// Currently working

////////////////////////////////////////////////////////////////////
// Automatic takes care of setup() and loop()
#define DEBUG_QIT
#include "Automatic.h"
// qit.h imports all the basic quickly interfacing templates
#include "qit.h"

// Testing the mini stack
#include "qitc_minimulti.h"

// we use this namespace so it comes to scope
using namespace qit;

container::MiniMulti< int , 8 > mltTest;

// we construct a binary led component that interfaces
LED< LED_BUILTIN > ledBuiltin;

// construct a button object, 7 is the pin number, the function
// passed is called a lambda, or a referenced function
Button< 7 > btnToggleLed([](bool pressed) {
  // is a button pressed?
  if (pressed) {
    // yes, then toggle the led component
    ledBuiltin.toggle();
  }
});

