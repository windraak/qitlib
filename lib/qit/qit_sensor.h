
#ifndef H_SENSORS_QIT
#define H_SENSORS_QIT

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Sensor for the SensorServer
 * /!\ LL means linked list.
 */

#include <Arduino.h>

namespace qit
{

// Abstract class
struct Sensor
{
public:
  // Which would be the next sensor to pull? LL for data saving
  Sensor *next = 0;
  // Are we being polled?
  bool enabled = true;
  // Execute every sensorserver heartbeat
  virtual void beat() { }
  // Initialised not at constructor
  virtual void initialize() { }
  
  void enable() { enabled = true; }
  void disable() { enabled = false; }
  void toggle() { enabled =! enabled; }

  // Sensor constructor does tell the server to agnostically add it
  Sensor();
};

// For self referencing in lambdas
Sensor* self = NULL;

// Keep track of the sensors
class SensorServer {
public:
  // What is the first sensor in the LL
  static Sensor* first;
  // Which was the last to which we may add a new one
  static Sensor* last;

  // Add one
  static void add(Sensor *which)
  {
    // Is root?
    if (last == NULL)
    {
      // Set 'm and return
      last = which;
      first = which;
      return;
    }
    
    // Link 'm
    SensorServer::last->next = which;
    SensorServer::last = which;
  }

  // Disable all sensors
  static void disableAll() {  
    Sensor *i = first;
next_sensor:
    if (i) {
      i->disable();
      i = i->next;
      goto next_sensor;
    }
  }

  // Update all sensors
  static void heartbeat() {
    // Start from which one
    Sensor *start = first;

    // Iterate 'm all
next_sensor:
    if (start)
    {
      // Only if it is enabled to poll does it beat
      if (start->enabled) {
        // This is the active sensor
        self = start;
        start->beat();
      }
      start = start->next;
      goto next_sensor;
    }
  }

  // Initialize all components from the LL
  // Simmilar as heartbeat but initialize the stuff and not beat
  static void initialize() {
    Sensor *start = first;
next_sensor:
    if (start)
    {
      start->initialize();
      start = start->next;
      goto next_sensor;
    }
  }
};

// Tell the compiler and linker to save some space for these
Sensor* SensorServer::first;
Sensor* SensorServer::last;

// Gnostic add the sensor to the SensorServer, sensor remembers itself
Sensor::Sensor() { SensorServer::add(this); }

}

#endif
