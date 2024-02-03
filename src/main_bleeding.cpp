/*
#include <Arduino.h>

#include "Automatic.h"
#include "qit.h"
#include "qit_buzzmusic.h"

#include "qit_potmeter.h"

qit::aux::BuzzerMusic< 12 > music;
qit::AnalogInputSensor< A0 , 32 > potmeter_test_amb;
qit::TimerThreads< 4 > timers;

qit::Button< 7 > myButton([](bool pressed) {
  if (pressed)
  {
    Serial.println("Button pressed");
    music.play("R");
    timers.after(5000, [](int t) { 
        Serial.println("5 seconds passed."); 
        timers.after(5000, [](int t) {
          Serial.println("Another 5 seconds passed.");
        });
      });
  }
  else
    Serial.println("Button unpressed");
 });


qit::PotMeter< A0 > potmeter([](int c) {
  // Serial.println(String(c));
  music.untone();
  music.tone(ACORD[3][c], 100);
});

qit::LED< LED_BUILTIN > myLed;


qit::Once onetime([](){
  Serial.println("Yes... Initialized.");
  timers.create(1000, 10, [](int r) { Serial.println(String(r)); });
  timers.create(500, FOREVER, [](int r) { 
    myLed.toggle(); 
    qit::Timer::active_timer->delaylength = 200 + (rand() % 800); 
  });
});

qit::Loop myLoop([]() {
  timers.heartbeat();
  if (myButton.pressed) {
    Serial.print("#");
  }
});



void setup() {
  Serial.begin(9600);
  Serial.println("Testing");
}

void loop() {
}*/

