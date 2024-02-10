
#define DEBUG_QIT
#include "AutomaticStated.h"
#include "Grove.h"

namespace Components {

  Grove::Button< 3 > btnMain;

}

CreateState(MainEntry);
CreateState(KnightState);
CreateStatemachine(MainEntry, 8);

void MainEntry::init() {
  Serial.println("I am the knight that says ni");

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
