
#ifndef H_ANA_COMP_QIT
#define H_ANA_COMP_QIT

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Simpler analog component interface
 */

#include <Arduino.h>
#include "qit_sensor.h"

namespace qit
{

// For leniancy
template < typename T >
inline bool Range(T value, T start, T end) {
    return value >= start && value <= end;
}

// A generic analog sensor to be extended by others
template < int PIN , int PRECISION = 16 , int LENIANCY = 1 >
class AnalogInputSensor : public Sensor {
public:
    AnalogInputSensor() : Sensor() { }

    // Remember the (A0-xx) pin, buffer the last read, and hold the
    // function callback.
    const int pin = PIN;
    int last_read = 0;
    int red = 0;

    // So it doesn't keep firing
    const int leniancy = LENIANCY;

    // Called by SensorServer init
    void initialize() {
        // A potentiometer for example is an analog input pin
        ::pinMode(PIN, INPUT);
        // So that it doesn't emediatly fire
        // !!! may have to add leniancy
        last_read = map(::analogRead(pin), 0, 1023, 0, PRECISION);
    }

    // For interface in inheritance
    inline int read() { 
        return map(::analogRead(pin), 0, 1023, 0, PRECISION);
    }

    void beat() {
        // Read the resistance
        red = read();
        
        // It's changed
        if (abs(red - last_read) > leniancy) {
            // Remember the last change
            last_read = red;
            // Callback the change only for derived classes
            // If this is used as a generic class it is intended for
            // passive reading from the global namespace
            // changed(red);
        }
    }
};

}

#endif
