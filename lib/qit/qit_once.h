
#ifndef H_ONCE_QIT
#define H_ONCE_QIT

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Add code that is once started during initialisation
 */

#include "qit_sensor.h"

namespace qit
{

// Callback is a simpel void function
typedef void (*__loop_callback) ();

class Once : Sensor {
public:
    __loop_callback callback = 0;

    Once(__loop_callback cb) : callback(cb) { }

    void initialize() {
        if (callback) callback();
        this->disable();
    }

    // ??? maybe add if (this->enabled condition)
    void again() { callback(); }

};

}

#endif
