#ifndef H_BINARY_QIT
#define H_BINARY_QIT

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Simple binary output for arduino
 */

#include <Arduino.h>

namespace qit
{

// Default pin is on board, so that you can quickly use it
template< int PIN_NUMBER = LED_BUILTIN >
class BinaryComponent
{
public:
    // Keep track whether it is on
    bool is_on = false;
    
    // Enable it when the class is constructed, doesn't have to be
    // as a sensor
    BinaryComponent() {
        ::pinMode(PIN_NUMBER, OUTPUT);
    }

    // Control functions for led, toggle being the only useful
    void on() { is_on = true; digitalWrite(PIN_NUMBER, HIGH); }
    void off() { is_on = false; digitalWrite(PIN_NUMBER, LOW); }
    inline void toggle() { if (is_on) off(); else on(); }

    // By read
    bool byRead() { return ::digitalRead(PIN_NUMBER); }

};

}

#endif
