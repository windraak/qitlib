/*
 * (cc-0) Joey Peters
 * Example that makes a timer that waits 3 seconds and then toggles
 * the buildin led.
 */

////////////////////////////////////////////////////////////////////
// Automatic takes care of setup() and loop()
#include "Automatic.h"

// we construct a binary led component that interfaces
LED< LED_BUILTIN > ledBuiltin;

// we allocate a few timers, in this case 8
// so we can press the button 8 times
Timers< 8 > timThread;

// on pin 7 we put a button
Button< 7 > btnDelayPrint([](bool pressed) {

  // is it being pressed or unpressed?
  if (pressed) {

    Serial.println("Waiting for 3 seconds to toggle.");

    // after 3 seconds toggle
    timThread.after(3000, [](int irrelevant) {
        Serial.println("Toggled.");
        ledBuiltin.toggle();
    });
    
  }
  
});
