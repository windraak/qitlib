
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
    byte _loc;

    // Some basic stack functionality
public:
    MiniMulti< T , BUFFER_SIZE >() { _loc = 0; }

    byte count() { return _loc; };

    // The common stuff
    T top() { 
        if (_loc > 0 && _loc < BUFFER_SIZE) 
            return _data[_loc - 1];
        return NULL; 
    }

    inline void pop() { if(_loc) _loc --; }
    
    void push(T what) { _data[_loc < BUFFER_SIZE ? _loc : BUFFER_SIZE] = what; _loc++; }

    // Some operator overloading. Add more stuff later
    // inline T* operator[] (int w) { return &_data[w]; }
};

}

#endif

