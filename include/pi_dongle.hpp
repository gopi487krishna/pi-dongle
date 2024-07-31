#ifndef __PI_DONGLE__
#define __PI_DONGLE__


#include <libinput.h>
#include <libudev.h>

struct report {
  unsigned char modifiers;
  unsigned char reserved;
  unsigned char key1;
  unsigned char key2;
  unsigned char key3;
  unsigned char key4;
  unsigned char key5;
  unsigned char key6;
};


struct modifier_state {
  unsigned left_ctrl  : 1;
  unsigned left_shift : 1;
  unsigned left_alt   : 1;
  unsigned left_gui   : 1;
  unsigned right_ctrl : 1;
  unsigned right_shift: 1;
  unsigned right_alt  : 1;
  unsigned right_gui  : 1;
};

struct pidongle_context {
  libinput *libinput_context;
  udev *udev_context;
  modifier_state modifier_state;
};



pidongle_context pidongle_init();
void pidongle_relay_events(pidongle_context& pidongle_context);

#endif
