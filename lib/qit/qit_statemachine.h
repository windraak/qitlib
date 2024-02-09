
#ifndef H_STATEM_QIT
#define H_STATEM_QIT

#include "qitc_minimulti.h"
#include "qit_debug.h"

namespace qit
{

// An automatic statemachine state
struct State {
public:

    virtual void init() {}
    virtual void beat() {}
    virtual void leave() {}
};

class RootState : public State {
public:
    void init() { Serial.println("Entering the bottom state stack."); }
};

// Create an automated statemachine
template < int SIZE = 8 >
class StateMachine : public qit::container::MiniMulti< State* , SIZE > {
public:

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

