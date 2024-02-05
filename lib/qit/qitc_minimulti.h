
#ifndef H_QIT_MINISTACK
#define H_QIT_MINISTACK

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Small stack functionality for statemachine (future addition)
 */

#include "Arduino.h"

namespace qit::container
{

// Because of limmited resources we make a mini stack (or general
// purpose container?) called MiniMulti
template <typename T , byte BUFFER_SIZE = 8 >
class MiniMulti {
private:
    // Not the most logical... But its a mini stack
    T _data[BUFFER_SIZE];
    T* _loc;

    // Some basic stack functionality
public:
    MiniMulti< T , BUFFER_SIZE >() { _loc = &_data[0]; }

    // The common stuff
    inline T* top() { return _loc - 1; }
    inline void pop() { _loc --; }
    void push(T what) { *_loc = what; _loc++; }

    inline bool inRange() { return _loc >= &_data[0] && _loc < &_data[BUFFER_SIZE]; }

    // Some operator overloading. Add more stuff later
    inline T* operator[] (int w) { return &_data[w]; }
};

}

#endif

