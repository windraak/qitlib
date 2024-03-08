
#ifndef H_TIMER_QIT
#define H_TIMER_QIT

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * A simple timer thread with timers. Limitted resources.
 */

#include "Arduino.h"

#if defined(ARDUINO_ARCH_NRF52) || defined(ARDUINO_ARCH_SAMD)
#include "ArduinoLowPower.h"
#endif

#include "qit_loop.h"

// For being passed to check if a timer runs indefently. signed int.
#define FOREVER -1

namespace qit {

// Timer function delegate type to be called when timer is fired
typedef void (*__timer_callback) (signed int repeat);

// Timer does not need a template
struct Timer {
  public:

  // Before the call back is called, active_timer is set to this so that
  // within the code clouse the timer can be accepted in the scope.
  static Timer* active_timer;

  // Tracking timer status
  bool enabled = false;
  bool disposed = true;

  inline void enable() { this->enabled = true; }
  inline void disable() { this->enabled = false; }
  inline void toggle() { this->enabled =! this->enabled; }

  inline void dispose() { this->disable(); this->disposed = true; }

  // The actual delegate to keep the callback for the individual timer
  __timer_callback callback;

  // The next turn is kept so that the timer has extra precession
  unsigned long next_turn = 0;
  // Interval
  unsigned int delaylength = 1000;
  // How many times fire repeat
  signed int repeat = FOREVER;

  // Timer is sense checked
  void beat() {
    // Timer is disabled so we don't do anything
    if (!enabled) return;

    // Current time checked and buffered because of precission
    unsigned long turned = ::millis();
    if (turned > next_turn)
    {
      // Now the program flow knows globally we're dealing with this
      // timer
      Timer::active_timer = this;
      
      // If it's going on forever we don't care and just callback
      if (repeat == FOREVER)
        this->callback(-1);
      else
      {
        // Otherwise the amount of times we will repeat is will be
        // counted down up to 0
        repeat--;

        // It is still more than 0 x time
        if (repeat >= 0)
          this->callback(repeat);
        else
          // It isn't so let's dispose of this one
          this->dispose();
      }
      // Buffered for more precission
      next_turn = turned + this->delaylength;
    }
  }
};

// Tells the linker and compiler that there is a static variable
Timer* Timer::active_timer;

// Create a template thread so it becomes scalable (since timers
// have a certain footprint on low mem boards. Even on those you may
// still want to use timers.
// !! DEPRICATED
template <int NUM_TIMERS = 8, bool AUTO_LOOP = true>
class Timers : public Sensor {
public:

  // Create a fixed number of timers and alocate them.
  Timer timers[NUM_TIMERS];

  // Check all timers and make them tick
  void beat() {
    
    for (Timer& i : timers)
      i.beat();
      
  }

  void initialize() { }

  // Get a timer from the slots that is not disposed
  Timer* getFree() {
    for(Timer& i : timers)
      if (i.disposed)
      {
        i.disposed = false;
        return &i;
      }
    
    // Sanity check should actually be done here at one point
    return NULL;
  }

  // And behold we create a timer
  Timer* create(unsigned int lngth, signed int repeat = FOREVER, __timer_callback tc = [](unsigned int i){}) {
    // Get a free one from the slots
    Timer* gotten = this->getFree();
    // If we dont find one...
    if (!gotten)
      return NULL;
    
    // Configured by the parameters
    gotten->callback = tc;
    gotten->repeat = repeat;
    gotten->next_turn = ::millis() + lngth;
    gotten->enable();
    gotten->delaylength = lngth;
    return gotten;
  }

  // A timer after a certain time
  Timer* after(unsigned int lngth, __timer_callback tc = [](int l) {})
  {
    Timer* which = this->getFree();

    if (!which)
      return NULL;

    which->callback = tc;
    which->next_turn = ::millis() + lngth;
    which->repeat = 1;
    which->enable();

    return which;
  }

  // A timer forever
  Timer* forever(unsigned int interval, __timer_callback tc = [](int l) {})
  {
    Timer* which = this->getFree();

    if (!which)
      return NULL;

    which->callback = tc;
    which->delaylength = interval;
    which->next_turn = ::millis();
    which->repeat = FOREVER;
    which->enable();

    return which;
  }

#if defined(ARDUINO_ARCH_NRF52) || defined(ARDUINO_ARCH_SAMD)

  void tryToIdle(unsigned int threshold = 1000) {
    
      long now = ::millis();
      for (Timer& i : timers)
        if (i.enabled)
          if ((i.next_turn -  now) < threshold)
            return;

      LowPower.idle((int)threshold);
      
  }

#else

  inline void tryToIdle(unsigned int threshold = 1000) { }

#endif

};

}

#endif
