
// Working test for qitlib here

// So we can serial print and take out serial print easily
#define DEBUG_QIT
#include <Automatic.h>
#include <QitContainers.h>
#include "qit_statemachine.h"

LED< LED_BUILTIN > ledBuildin;
MiniMulti< int , 8 > stackMini;

// Set the right pins! Mutual exclusive so callback is added later
ButtonLongPress< 7, 5000 > butTest([](unsigned long time) {
  qit_debug(String(time));
});

Button< 7 > butTest2([](bool pressed) {
  if (pressed)
    qit_debug("Pressed!");
  else
    qit_debug("Unpressed!");
});

// Only need one timer
Timers< 1 > timTimers;

// Testing statemachines
StateMachine< 8 > stmMine;

class WorkingState : public State {
  void beat() { qit_debug("Yuppers."); }
  void init() {}
  void leave() {}
};

WorkingState testState;

Once onceMain([]() {
  
  qit_debug("Starting up.");

  stmMine.addstate(&testState);

/*
  stackMini.push(22);
  stackMini.push(33);

  qit_debug(String(*stackMini.top()));

  stackMini.pop();

  qit_debug(String(*stackMini.top()));
*/

});

Loop updStates([]() {
  stmMine.heartbeat();
});
