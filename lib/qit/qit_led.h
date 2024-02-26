
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

// A led is actually just a binary pin component
template < int NUM >
using LED = BinaryComponent< NUM >;

// Automatic state for flickering a LED or binary component
template < int NUM >
class LEDFlicker : public State , public LED < NUM > {
public:
    // Some local stuff so we don't have to use a timer class
    unsigned long interval = 1000;
    unsigned char repeat = 3;
    unsigned long next;

public:

    // This could sometimes be useful except for static stuff
    LEDFlicker < NUM >(int interv, byte repe) : 
        interval(interv), repeat(repe) { }
    
    LEDFlicker < NUM >() { }

    // A LED state doesn't have anything going on for exit
    void leave() { }

    // But we do want to check when it flickers
    void beat() { 
        unsigned long current = ::millis();
        // Triggered at past a certain time
        if (current >= next) {
            // Re trigger later after interval
            next = current + interval;
            // The actual functionality
            this->toggle();
            // Should it be repeated?
            if (--repeat <= 0) {
                // It ends. So we exit the state
                GetStateMachine()->exitstateHard();
            }
        }
    }
};

// The actual function for flickering LEDs
template< int NUM >
void FlickerLed(byte howoften = 10, unsigned long interv = 1000) {
    // Create a state
    static LEDFlicker< NUM > whatLed;
    
    // Configure the state
    whatLed.repeat = howoften;
    whatLed.interval = interv;
    whatLed.next = ::millis();

    // Add the state
    GetStateMachine()->addstate(&whatLed);
};

}

#endif
