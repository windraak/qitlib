
#ifndef H_AUTOSTATE_QIT
#define H_AUTOSTATE_QIT

#include "qit_statemachine.h"
#include "qit.h"

using namespace qit;

#define CreateStatemachine(WHICH, SIZE)                     \
                                                            \
TStateMachine< SIZE > StateMachine;                         \
WHICH __state_init;                                         \
                                                            \
void setup() {                                              \
    Serial.begin(9600);                                     \
    while (!Serial);                                        \
    SensorServer::initialize();                             \
    delay(2500);                                            \
}                                                           \
                                                            \
void loop() {                                               \
    StateMachine.addstate(&__state_init);                   \
    while (StateMachine.top() != NULL) {                    \
        SensorServer::heartbeat();                          \
        StateMachine.heartbeat();                           \
    }                                                       \
}                                                           \

#define CreateState(WHICH)                                  \
class WHICH : public State {                                \
public:                                                     \
    void init();                                            \
    void beat();                                            \
    void leave();                                           \
};                                                          \

#endif
