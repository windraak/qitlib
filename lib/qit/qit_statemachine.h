
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

    inline void heartbeat() {
        this->top()->beat();
    }

    inline void exitstate() {
        this->top()->leave(); 
        this->pop(); 
    }

    inline void addstate(State* which) {
        this->push(which);
        this->top()->init();
    }
};

}

#endif

