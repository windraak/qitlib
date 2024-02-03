
// So we can serial print and take out serial print easily
#define DEBUG_QIT
#include <Automatic.h>

LED< LED_BUILTIN > ledBuildin;

// Set the right pins! Mutual exclusive so callback is added later
ButtonLongPress< 7, 5000 > butTest([](unsigned long time) {
  qit_debug(String(time));
});

Button< 7 > butTest2([](bool pressed) {
  if (pressed)
    qit_debug("Pressed!");
  else
    qit_debug("Unpressed!");
});

// Only need one timer
Timers< 1 > timTimers;

Once onceMain([]() {
  
  qit_debug("Starting up.");

});

