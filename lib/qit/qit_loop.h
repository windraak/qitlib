
#ifndef H_LOOPER_QIT
#define H_LOOPER_QIT

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Add code that is always executed
 */

#include "qit_sensor.h"

namespace qit
{

// Callback is a simpel void function
typedef void (*__loop_callback) ();

// Hijack the sensor stuff
class Loop : public Sensor {
public:
    __loop_callback looping;

    // Constructor for global construction
    Loop(__loop_callback l) : Sensor(), looping(l) { }

    // Do it at every sensor server heart beat
    void beat() { looping(); }
};

}

#endif