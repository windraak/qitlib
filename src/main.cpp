
#define DEBUG_QIT
#include "AutomaticStated.h"
#include "Grove.h"
#include "qit_functions.h"

Functions< 8 > differentGreet;

namespace Components {

  Button< 7 > btnMain;

}

CreateState(MainEntry);
CreateState(KnightState);
CreateState(EnemyState);
CreateStatemachine(MainEntry, 8);

void MainEntry::init() {

  differentGreet.clear();
  
  Serial.println("ENTERING BATTLEFIELD");

  // Testing function tuples

  differentGreet.addFunction([]() { Serial.println("Looking for enemies..."); });

  differentGreet.addFunction([]() { Serial.println("We're in the fields..."); });

  differentGreet.addFunction([]() { Serial.println("Something looks ominous..."); });

  differentGreet.random();
  differentGreet.random();
  differentGreet.random();
  differentGreet.random();

  while(!Serial);
  // differentGreet.get_ref(0)->call();
  // differentGreet.yield();

  Components::btnMain.callback = [](bool pressed) {
    if (pressed) {
      static KnightState ks;
      StateMachine.addstate(&ks);
    }
  };

}

void MainEntry::beat() { }

void MainEntry::leave() {
    Serial.println("And I have to go");
}

///////////////////////////////////////////////////////////////////////////

int hits = 3;

void KnightState::init() {
  Serial.println("The knight takes three hits");
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
  Serial.println("I have been defeated!");
}

void KnightState::beat() { }

///////////////////////////////////////////////////////////////////////////

void EnemyState::init() {
  Serial.println("The skeleton takes 2 hits");
  hits = 2;

  Components::btnMain.callback = [](bool pressed) {
    if (pressed) {
      if (--hits==0) {
        StateMachine.exitstate();
      }
    }
  };
}

void EnemyState::leave() {
  Serial.println("I have been defeated!");
}

void EnemyState::beat() { }
