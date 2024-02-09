
#define DEBUG_QIT
#include "AutomaticStated.h"

namespace Components {

  Button< 7 > btnMain;

}

CreateState(MainEntry);
CreateStatemachine(MainEntry, 8);

void MainEntry::init() {
  Serial.println("I am the knight that says ni");
  Components::btnMain.callback = [](bool pressed) {
    if (pressed)
      Serial.println("You done just hit me with that.");
  };
}

void MainEntry::beat() {
    // Serial.println("Crazy");
}

void MainEntry::leave() {
    Serial.println("And I have to go");
}
