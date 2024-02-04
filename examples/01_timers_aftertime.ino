/*
 * (cc-0) Joey Peters
 * Example that makes a timer that waits 3 seconds and then toggles
 * the buildin led.
 */

////////////////////////////////////////////////////////////////////
// Automatic takes care of setup() and loop()
#include "Automatic.h"
// qit imports all the basic quickly interfacing templates
#include "qit.h"

// we use this namespace so it comes to scope
using namespace qit;

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

// we tell qit that once the program starts it creates a few
// timers.
Once fncCreateTimers([]() {
  // every 5 seconds toggle the led
  Serial.println("Booting.");
});
