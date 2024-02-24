/*
 * (cc-0) Joey Peters
 * Example that flickers the light at random intervalls for 8 times
 * per button press. Upload and press the button a few times and
 * look and wait at the board led
 * 
 */

////////////////////////////////////////////////////////////////////
// Automatic takes care of setup() and loop()
#include "Automatic.h"

// we construct a binary led component that interfaces
LED< LED_BUILTIN > ledBuiltin;

// we allocate a few timers, in this case 8 simaltanious pushes
Timers< 8 > timThread;

// on pin 7 we put a button
Button< 7 > btnDelayPrint([](bool pressed) {

  // is it being pressed or unpressed?
  if (pressed) {

    // we pressed it, know it
    Serial.println("Button pressed. Random toggler for 5 cycles");

    // create a random interval blinker for 8 repeats
    timThread.create(100 + (::rand() % 1000) , 8, [](int rep) {

      // count down
      Serial.print("Toggler active for x more times: ");
      Serial.println(String(rep));

      // toggle it every interval
      ledBuiltin.toggle();

    }); 
  }
  
});

