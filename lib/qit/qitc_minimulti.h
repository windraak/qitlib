
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
public:
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
        return _data[BUFFER_SIZE - 1]; 
    }

    T* top_ref() { return &_data[_loc]; }

    void inc() { _loc++; if (_loc >= BUFFER_SIZE) _loc = BUFFER_SIZE - 1; }

    T get(int index) {
        if (index >= 0 && index < BUFFER_SIZE)
            return _data[index];
        return _data[BUFFER_SIZE - 1];
    }

    T* get_ref(int index) {
        if (index >= 0 && index < BUFFER_SIZE)
            return &_data[index];
        return &_data[BUFFER_SIZE - 1];
    }

    inline void pop() { if(_loc) _loc --; }
    
    void push(T what) { 
        _data[_loc < BUFFER_SIZE ? _loc : BUFFER_SIZE - 1] = what; 
        _loc++; 
    }

    void clear() { _loc = 0; }

    // Some operator overloading. Add more stuff later
    inline T* operator[] (int w) { 
        return &_data[w < BUFFER_SIZE ? _loc : BUFFER_SIZE - 1]; 
    }
};

}

#endif

