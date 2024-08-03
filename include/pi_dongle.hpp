#ifndef __PI_DONGLE__
#define __PI_DONGLE__


#include <cstdint>
#include <libinput.h>
#include <libudev.h>
#include <fstream>


struct modifier_state {
  unsigned left_ctrl  : 1;
  unsigned left_shift : 1;
  unsigned left_alt   : 1;
  unsigned left_gui   : 1;
  unsigned right_ctrl : 1;
  unsigned right_shift: 1;
  unsigned right_alt  : 1;
  unsigned right_gui  : 1;
}__attribute__((packed));

struct report {
  modifier_state modifiers;
  std::uint8_t reserved;
  std::uint8_t key1;
  std::uint8_t key2;
  std::uint8_t key3;
  std::uint8_t key4;
  std::uint8_t key5;
  std::uint8_t key6;
} __attribute__((packed));


struct pidongle_context {
  libinput *libinput_context;
  udev *udev_context;
  modifier_state mod_state = {0};
  int dev_fd;
};



pidongle_context pidongle_init();
void pidongle_relay_events(pidongle_context& pidongle_context);

#endif
