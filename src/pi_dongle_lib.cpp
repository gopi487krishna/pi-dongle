#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <libinput.h>
#include <iostream>
#include <fcntl.h>
#include <libudev.h>
#include <string>
#include <unistd.h>
#include <pi_dongle.hpp>
#include <linux/input-event-codes.h>

static void check_condition(bool condition, const std::string& faliure_message) {
  if (!condition) {
    std::cerr << "condition faliure : " << faliure_message << '\n';
    std::exit(EXIT_FAILURE);
  }
}

static int open_restricted(const char* path, int flags, void* user_data)
{
  int fd = open(path, flags);
  return fd < 0 ? -errno : fd;
}

static void close_restricted(int fd, void* user_data)
{
  close(fd);
}

const static struct libinput_interface interface = {
  .open_restricted = open_restricted,
  .close_restricted = close_restricted,
};


pidongle_context pidongle_init() {
  pidongle_context pidongle_context;
  udev* udev_context = udev_new();
  check_condition(udev_context, "Failed to create udev context\n");

  libinput* libinput_context = libinput_udev_create_context(&interface, NULL, udev_context);
  check_condition(libinput_context, "Failed to create libinput context\n");

  int status = libinput_udev_assign_seat(libinput_context, "seat0");
  check_condition(status == 0, "Failed to assign seat to libinput_context");

  pidongle_context.udev_context = udev_context;
  pidongle_context.libinput_context = libinput_context;

  return pidongle_context;
}

static bool is_modifier_key(uint8_t key) {
  return key == KEY_LEFTCTRL || key == KEY_LEFTSHIFT || key == KEY_LEFTALT ||
         key == KEY_LEFTMETA || key == KEY_RIGHTCTRL || key == KEY_RIGHTSHIFT ||
         key == KEY_RIGHTALT || key == KEY_RIGHTMETA;
}

static void update_modifier_state(uint8_t key, pidongle_context &context) {
  switch (key) {
  case KEY_LEFTCTRL:
    context.mod_state.left_ctrl ^= 1;
    break;
  case KEY_LEFTSHIFT:
    context.mod_state.left_shift ^= 1;
    break;
  case KEY_LEFTALT:
    context.mod_state.left_alt ^= 1;
    break;
  case KEY_LEFTMETA:
    context.mod_state.left_gui ^= 1;
    break;
  case KEY_RIGHTMETA:
    context.mod_state.right_gui ^= 1;
    break;
  case KEY_RIGHTCTRL:
    context.mod_state.right_ctrl ^= 1;
    break;
  case KEY_RIGHTSHIFT:
    context.mod_state.right_shift ^= 1;
    break;
  case KEY_RIGHTALT:
    context.mod_state.right_alt ^= 1;
    break;
  default:
    std::cerr << "Trying to update invalid modifier key";
  }
}
static void send_release_report(pidongle_context &context) {
  std::uint64_t report = 0; 
}
static void send_input_report(uint8_t key, pidongle_context &context) {
  /* 
   * 0 byte represents the modifier mask
   * 1 byte is reserved
   * 2 - 7 : keys
   */
  std::uint64_t report = 0;
  unsigned char* modifier_mask = (unsigned char*)&context.mod_state;
  report = ((std::uint64_t)*modifier_mask << 56);
  report = ((std::uint64_t)key << 46);
}

static void relayKeyboardEvent(libinput_event_keyboard* keyboard_event, pidongle_context& context)
{
  libinput_key_state key_state = libinput_event_keyboard_get_key_state(keyboard_event);
  uint8_t key = (uint8_t)libinput_event_keyboard_get_key(keyboard_event);

  switch (key_state) {
  case LIBINPUT_KEY_STATE_PRESSED: {
      if (is_modifier_key(key)) {
        update_modifier_state(key, context);
      }
      send_input_report(key, context);
      break;
  }
  case LIBINPUT_KEY_STATE_RELEASED: {
    send_release_report(context);
    break;
  }
  }
}

void pidongle_relay_events(pidongle_context& pidongle_context) {

  check_condition(pidongle_context.libinput_context, "libinput_context null");
  check_condition(pidongle_context.udev_context, "udev_context null");

  /* Event loop to detect keyboard events */
  libinput_event* event = nullptr;
  while(true) {

    libinput_dispatch(pidongle_context.libinput_context);
    event = libinput_get_event(pidongle_context.libinput_context);

    if (!event) {
      continue;
    }

    /* Only look for keyboard events */
    if (libinput_event_get_type(event) == LIBINPUT_EVENT_KEYBOARD_KEY) {
      libinput_event_keyboard* keyboard_event = libinput_event_get_keyboard_event(event);
      relayKeyboardEvent(keyboard_event, pidongle_context);
    }

    libinput_event_destroy(event);
  }
}
