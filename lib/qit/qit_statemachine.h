
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
    virtual void beat() { }
    virtual void leave() {}
};

// Create an automated statemachine
template < int SIZE = 8 >
class StateMachine : public qit::container::MiniMulti< State* , SIZE > {
public:

    void heartbeat() {
        this->top()->beat();
    }

    void exitstate() {
        this->top()->leave(); 
        this->pop();
        this->top()->init();
    }

    void addstate(State* which) {
        this->push(which);
        which->init();
    }
};

}

#endif

