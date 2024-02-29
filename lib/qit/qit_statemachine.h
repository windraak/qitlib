
#ifndef H_STATEM_QIT
#define H_STATEM_QIT

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Keep track of states
 */

#include "qitc_minimulti.h"
#include "qit_sensor.h"

namespace qit
{

// An automatic statemachine state
struct State {
public:
    // These are all the functionalities for states
    virtual void init() {}
    virtual void beat() {}
    virtual void leave() {}
};

// For if we don't need to do anything except listen to sensors
class __NothingState : public State { };
__NothingState NothingState;

class IStateMachine {
private:
    // ! This is actually bad practise but it seems useful
    static IStateMachine* singleton;
public:
    // Things that should be implemented for a statemachine
    virtual void heartbeat();
    virtual void exitstate();
    virtual void exitstateHard();
    virtual void addstate(State*);
    virtual void awaitExit();

    // ! This is part of the bad practice
    static void setSingleton(IStateMachine *wh) { singleton = wh; }
    static IStateMachine* getSingleton() { return singleton; }
};

// Make some space for this
IStateMachine* IStateMachine::singleton;

// The actual singleton functionality. Useful for anonymous access
IStateMachine* GetStateMachine() { return IStateMachine::getSingleton(); };

// Create an automated statemachine
template < int SIZE = 8 >
class TStateMachine : 
    public IStateMachine, 
    public qit::container::MiniMulti< State* , SIZE > {
public:

    // It is initialized, which makes it the singleton
    TStateMachine< SIZE >() { IStateMachine::setSingleton(this); }

    // The main loop stuff
    void heartbeat() {
        this->top()->beat();
    }

    // Neatly exit a state
    void exitstate() {
        // For safety
        if (this->top() == NULL)
            return;
        this->top()->leave(); 
        this->pop();
        // For safety
        if (this->top() == NULL)
            return;
        this->top()->init();
    }

    // If we want to exit but not call inits or leaves
    void exitstateHard() {
        if (this->top() == NULL)
            return;
        this->pop();
    }

    // Yes please
    void addstate(State* which) {
        which->init();
        this->push(which);
    }

    // So we can use it pseudo threaded
    void awaitExit() {
        // Remember which we are now
        State* current = this->top();
        // Safety check
        if (current == NULL)
            return;
        // Sometimes awaitexit is called in a component, so
        // we buffer it.
        Sensor* bufferme = self;
        // Is it changed within the state?
        while (this->top() == current) {
            SensorServer::heartbeat();
            this->heartbeat();
        }
        self = bufferme;
        // Yes it has changed so now we can end the function
    }

};

}

#endif

