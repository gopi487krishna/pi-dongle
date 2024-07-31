#include "pi_dongle.hpp"




int main() {
  pidongle_context pidongle_context = pidongle_init();
  pidongle_relay_events(pidongle_context);
  
}

