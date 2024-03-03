
#ifndef H_QIT_ONCE
#define H_QIT_ONCE

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Include all the qit components, sensors, timers and all other
 * features.
 */

#ifndef QIT_DELAY
#define QIT_DELAY
#include "qit_sensor.h"
// Not ideally placed but ok
namespace qit { 
    void qit_delay(unsigned long howlong) {
        unsigned long until = ::millis() + howlong;
        while(::millis() < until)
            SensorServer::heartbeat();
    }
}
#endif

// include the whole rim-bam, not compiler efficient but it works
// conveniantly
#include "qit_debug.h"
#include "qit_analog_sensor.h"
#include "qit_potmeter.h"
#include "qit_binary_component.h"
#include "qit_button.h"
#include "qit_led.h"
#include "qit_loop.h"
#include "qit_once.h"
#include "qit_timer.h"
#include "qit_functions.h"
#include "qit_temperature.h"

#endif
