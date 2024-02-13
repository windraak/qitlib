
#define DEBUG_QIT
#include "AutomaticStated.h"
#include "Grove.h"
#include "qit_functions.h"

Functions< 8 > enemies;

namespace Components {

  Button< 7 > btnMain;

}

CreateState(MainEntry);
CreateState(KnightState);
CreateState(EnemyState);
CreateStatemachine(MainEntry, 8);

void MainEntry::init() {

  enemies.clear();
  
  // Serial.println("ENTERING BATTLEFIELD");

  // // Testing function tuples

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

  // differentGreet.addFunction([]() { Serial.println("We're in the fields..."); });

  // differentGreet.addFunction([]() { Serial.println("Something looks ominous..."); });

  // differentGreet.random();
  // differentGreet.random();
  // differentGreet.random();
  // differentGreet.random();

  // while(!Serial);
  // differentGreet.get_ref(0)->call();
  // differentGreet.yield();

  qit_debug("We're in the fields...");

  Components::btnMain.callback = [](bool pressed) {
    if (pressed) {
      Serial.println("Looking for enemies..."); 
      enemies.random();
    }
  };

}

void MainEntry::beat() { }

void MainEntry::leave() {
    qit_debug("And I have to go");
}

///////////////////////////////////////////////////////////////////////////

int hits = 3;

void KnightState::init() {
  qit_debug("The weak enemy takes three hits");
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
  Serial.println(F("The skelleton takes 5 hits"));
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
