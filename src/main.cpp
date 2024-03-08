#define DEBUG_QIT
#include <Automatic.h>

// Create a LED on builtin pin
LED < LED_BUILTIN > ledBuiltin;
Timers< 1 > tmrServer;
Timer *tmrToggler;

// Create a button
Button< 7 > btnToggler([](bool pressed) {
  // Are we pressed?
  if (pressed) 
    // Toggle the timer
    tmrToggler->toggle();
});

// Once initialize the timers
Once onceCreateTimers([]() {
  // !!! Remember the timer into the global variable scope
  tmrToggler = tmrServer.forever(1000, [](int cll) {
    // Toggle the led
    ledBuiltin.toggle();
  });
});

/*
// Include the basis statemachine macros
#include "AutomaticStated.h"

Functions< 8 > enemies;

namespace Components {

  Button< 7 > btnMain;

}

// Create the states
CreateState(MainEntry);
CreateState(KnightState);
CreateState(EnemyState);
CreateStatemachine(MainEntry, 8);

// When we enter the state, do the following
void MainEntry::init() {

  enemies.clear();
  
  enemies.addFunction(
    []() { 
      static KnightState ks;
      StateMachine.addstate(&ks);
    });
  
  enemies.addFunction(
    []() { 
      static EnemyState es;
      StateMachine.addstate(&es);
    });

  qit_debug("We're in the fields...");

  Components::btnMain.callback = [](bool pressed) {
    if (pressed) {
      Serial.println("Looking around..."); 
      enemies.random();
    }
  };

}

void MainEntry::beat() { }

// This would probably never happen
void MainEntry::leave() {
    qit_debug("And I have to go");
}

///////////////////////////////////////////////////////////////////////////

int hits = 3;

void KnightState::init() {
  qit_debug("The weak enemy knight takes three hits");
  hits = 3;

  Components::btnMain.callback = [](bool pressed) {
    if (pressed) {
      if (--hits==0) {
        StateMachine.exitstate();
      }
    }
  };
}

void KnightState::leave() {
  qit_debug("I have been defeated!");
}

void KnightState::beat() { }

///////////////////////////////////////////////////////////////////////////

void EnemyState::init() {
  Serial.println("The skelleton takes 5 hits");
  hits = 5;

  Components::btnMain.callback = [](bool pressed) {
    if (pressed) {
      if (--hits==0) {
        StateMachine.exitstate();
      }
    }
  };
}

void EnemyState::leave() {
  Serial.println("I, the mighty skelleton have been defeated!");
}

void EnemyState::beat() { }
*/