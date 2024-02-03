
#ifndef H_AUTOMATIC
#define H_AUTOMATIC

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Boot and loop, take over from user declared loop and setup
 */

#include <Arduino.h>
#include "qit.h"

using namespace qit;

void setup() {
  // ! we may change this one day
  Serial.begin(9600);
  SensorServer::initialize();
}

void loop() {
  SensorServer::heartbeat();
}

#endif
