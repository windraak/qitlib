
#ifndef H_POTMETER_QIT
#define H_POTMETER_QIT

#include "qit_analog_sensor.h"

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Potmeter uses the analog sensor
 */

namespace qit 
{

// callback bound to changed values in sensor
typedef void (*__analog_callback) (int);

template < int PIN , int PRECISION = 16 , int LENIANCY = 1 >
class PotMeter : public AnalogInputSensor < PIN , PRECISION , LENIANCY >
{
public:
    __analog_callback changed;

    // We do take a callback for integer changes between precision with
    // a certain leniancy.
    PotMeter(__analog_callback c) 
        : AnalogInputSensor< PIN , PRECISION , LENIANCY>(), changed(c) { }

    // ovveride the read
    void beat() {
        // Read the resistance
        this->red = this->read();
        // It's changed
        if (abs(this->red - this->last_read) > this->leniancy) {
            // Remember the last change
            this->last_read = this->red;
            // Callback the change
            changed(this->red);
        }
    }
};

}

#endif
