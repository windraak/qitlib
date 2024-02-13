
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

typedef void (*VoidFunction) ();

struct FunctionTuple {
public:
    VoidFunction function { };
    unsigned int called = 0;

    void call() {
        function();
        ++called;
    }
};

// I got clashes with the minimulti which needs work
template <int SIZE = 8>
class Functions {
public:
    byte rotating = 0;
    byte counter = 0;

    FunctionTuple my_function_tuples[SIZE];

    FunctionTuple* index(byte w) { return &my_function_tuples[w]; }

    void reset() { rotating = 0; counter = 0; }
    
    void yield() {
        my_function_tuples[rotating++].call();
        if (rotating >= counter)
            rotating = 0;
    }

    void random() {
        my_function_tuples[rand() % counter].call();
    }

    FunctionTuple* add() {
        return &my_function_tuples[counter++];
    }

    void all() { for(FunctionTuple i : my_function_tuples) i.call(); }

    void addFunction(VoidFunction which) {
        my_function_tuples[counter++].function = which;
    }

    void clear() {
        FunctionTuple empty;
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

