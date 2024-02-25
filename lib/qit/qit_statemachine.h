
#ifndef H_STATEM_QIT
#define H_STATEM_QIT

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Keep track of states
 */

#include "qitc_minimulti.h"

namespace qit
{

// An automatic statemachine state
struct State {
public:

    virtual void init() {}
    virtual void beat() {}
    virtual void leave() {}
};

class __NothingState : public State { };
__NothingState NothingState;

class IStateMachine {
private:
    static IStateMachine* singleton;
public:
    virtual void heartbeat();
    virtual void exitstate();
    virtual void addstate(State*);
    static void setSingleton(IStateMachine *wh) { singleton = wh; }
    static IStateMachine* getSingleton() { return singleton; }
};

IStateMachine* IStateMachine::singleton;

// Create an automated statemachine
template < int SIZE = 8 >
class TStateMachine : 
    public IStateMachine, 
    public qit::container::MiniMulti< State* , SIZE > {
public:

    TStateMachine< SIZE >() { IStateMachine::setSingleton(this); }

    void heartbeat() {
        this->top()->beat();
    }

    void exitstate() {
        if (this->top() == NULL)
            return;
        this->top()->leave(); 
        this->pop();
        if (this->top() == NULL)
            return;
        this->top()->init();
    }

    void addstate(State* which) {
        which->init();
        this->push(which);
    }

};

}

#endif

