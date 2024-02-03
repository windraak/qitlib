
#ifndef H_BUTTON_QIT
#define H_BUTTON_QIT

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * A simple button template which constructs with a constant pin.
 * Interfaces with sensor
 */

#include "qit_sensor.h"

namespace qit {

// Declare the delegate type
typedef void (*__button_callback) (bool);

// The actual template for a button class
template< int PIN_NUMBER , unsigned long DEBOUNCE = 40, bool USE_PULLUP = true >
class Button : public Sensor
{
public:
  // Not in progmem in arduino rev < 4 but ok
  const int pin = PIN_NUMBER;

  // Not gonna lie copy paste from arduino website (including stuff in beat())
  int lastButtonState = LOW; 
  unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay = DEBOUNCE;

  // Delegate called when the pin is pushed
  __button_callback callback;
  // Keep track of the button state
  bool pressed = false;

  // Because it may change what to do with the button, we can change
  // the button process.
  void bind(__button_callback cb) {
    callback = cb;
  }

  // Empty constructor
  Button() { }

  Button(__button_callback cb) : callback(cb) { }

  // So that global scope is evaluated first and not in constructor
  void initialize() {
    ::pinMode(pin, USE_PULLUP ? INPUT_PULLUP : INPUT);
    lastDebounceTime = millis();
    // lastButtonState = digitalRead(PIN_NUMBER);
  }

  // Sensor check
  void beat() {
    // Debounce
    int reading = digitalRead(PIN_NUMBER);

    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) {
      // reset the debouncing timer
      lastDebounceTime = millis();
    }

    // Is it noice?
    if ((millis() - lastDebounceTime) < debounceDelay) {
      return;
    }

    lastButtonState =! reading;

    // Is the pin not pressed and is it not being currently pressed?
    if (reading == LOW) {
      if (pressed == false)
      {
        pressed = true;
        // Then we pressed the button and call the delegate callback
        callback(true);
      }
    // It circuits?
    } else if (reading == HIGH) {
      if (pressed == true)
      {
        pressed = false;
        // Then we unpress the thing
        callback(false);
      }
    }
  }
};

typedef void (*__button_pressed_callback) (unsigned long);

// For when you need a callback for being pressed for X time
// The actual template for a button class
template< int PIN_NUMBER , unsigned int MAX_WAIT = 2500, bool USE_PULLUP = true >
class ButtonLongPress : public Sensor
{
public:
  // Not in progmem in arduino rev < 4 but ok
  const int pin = PIN_NUMBER;
  unsigned int max_wait = MAX_WAIT;

  unsigned long from_when = 0;

  // Delegate called when the pin is pushed
  __button_pressed_callback callback;
  // Keep track of the button state
  bool pressed = false;

  // Because it may change what to do with the button, we can change
  // the button process.
  void bind(__button_callback cb) {
    callback = cb;
  }

  // Empty constructor
  ButtonLongPress() { }

  ButtonLongPress(__button_pressed_callback cb) : callback(cb) { }

  // So that global scope is evaluated first and not in constructor
  void initialize() {
    ::pinMode(pin, USE_PULLUP ? INPUT_PULLUP : INPUT);
    from_when = ::millis();
  }

  // Sensor check
  void beat() {

    unsigned long now = ::millis();
    unsigned long passed = now - from_when;

    if (pressed && passed >= this->max_wait) {
      callback(passed);
      pressed = false;
    }

    // Is the pin not pressed and is it not being currently pressed?
    if (::digitalRead(PIN_NUMBER) == LOW) {
      if (pressed == false)
      {
        pressed = true;
        // Remember when started pressing
        from_when = ::millis();
      }
    // It circuits?
    } else if (::digitalRead(PIN_NUMBER) == HIGH) {
      if (pressed == true)
      {
        // Ignore noise from breadboards
        if (passed < 100) {
          from_when = now;
          return;
        }
        callback(passed);
        pressed = false;
        from_when = now;
      }
    }
  }
};

}

#endif
