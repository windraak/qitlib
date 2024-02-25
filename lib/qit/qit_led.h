
#ifndef H_LED_QIT
#define H_LED_QIT

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Simpler LED control derived from binary component
 */

#include <Arduino.h>
#include "qit_binary_component.h"

namespace qit
{

template < int NUM >
using LED = BinaryComponent< NUM >;

template < int NUM >
class LEDFlicker : public State , public LED < NUM > {
public:
    unsigned long interval = 1000;
    unsigned char repeat = 3;
    unsigned long next;

public:

    LEDFlicker < NUM >(int interv, byte repe) : 
        interval(interv), repeat(repe) { }
    
    LEDFlicker < NUM >() { }

    void init() { 
        next = ::millis() + interval;
    }
    void leave() { }
    void beat() { 
        unsigned long current = ::millis();
        if (current >= next) {
            next = ::millis() + interval;
            this->toggle();
            if (--repeat <= 0) {
                GetStateMachine()->exitstateHard();
            }
        }
    }
};

template< int NUM >
void FlickerLed(byte howoften = 10, unsigned long interv = 1000) {
    static LEDFlicker< NUM > whatLed;
    
    whatLed.repeat = howoften;
    whatLed.interval = interv;
    whatLed.next = ::millis();

    GetStateMachine()->addstate(&whatLed);
};

}

#endif
