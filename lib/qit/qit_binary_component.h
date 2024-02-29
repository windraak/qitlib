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

// Automatic state for flickering a LED or binary component
template < int NUM >
class BinFlicker : public State , public BinaryComponent < NUM > {
public:
    // Some local stuff so we don't have to use a timer class
    unsigned long interval = 1000;
    unsigned char repeat = 3;
    unsigned long next;

public:

    // This could sometimes be useful except for static stuff
    BinFlicker < NUM >(int interv, byte repe) : 
        interval(interv), repeat(repe) { }
    
    BinFlicker < NUM >() { }

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
void Flicker(byte howoften = 10, unsigned long interv = 1000) {
    // Create a state
    static BinFlicker< NUM > whatLed;
    
    // Configure the state
    whatLed.repeat = howoften;
    whatLed.interval = interv;
    whatLed.next = ::millis();

    // Add the state
    GetStateMachine()->addstate(&whatLed);
};

}

#endif
