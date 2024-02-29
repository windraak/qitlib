
#ifndef H_QIT_FUNCTIONS
#define H_QIT_FUNCTIONS

#include "Arduino.h"
#include "qitc_minimulti.h"

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Simple delegate yielding
 */

namespace qit
{

// Generally we'll only use void functions
typedef void (*VoidFunction) ();

// To remember how many times the function has been called
struct FunctionTuple {
public:
    VoidFunction function { };
    // Maybe later change to long?
    unsigned int called = 0;

    // Keep track of calls
    void call() {
        function();
        ++called;
    }
};

// I got clashes with the minimulti which needs work
template <int SIZE = 8>
class Functions {
public:
    // At what index are we yielding
    byte rotating = 0;
    // What is the current size of the stack
    byte counter = 0;

    // The actual functions
    FunctionTuple my_function_tuples[SIZE];

    // Basic access
    FunctionTuple* index(byte w) { return &my_function_tuples[w]; }

    // Back to zero
    void reset() { rotating = 0; counter = 0; }
    
    // ! The main functionality
    void yield() {
        my_function_tuples[rotating++].call();
        if (rotating >= counter)
            rotating = 0;
    }

    // This is sometimes useful for games and such
    void random() {
        my_function_tuples[rand() % counter].call();
    }

    // Yes. We are doing it this way. Don't judge
    FunctionTuple* add() {
        return &my_function_tuples[counter++];
    }

    // Execute all functions, sometimes useful
    void all() { for(FunctionTuple& i : my_function_tuples) i.call(); }

    // The container functions
    void addFunction(VoidFunction which) {
        my_function_tuples[counter++].function = which;
    }

    void clear() {
        for(FunctionTuple& i : my_function_tuples)
        {
            i.called = 0;
            i.function = []() { };
        }
        counter = 0;
        rotating = 0;
    }
};

}

#endif

