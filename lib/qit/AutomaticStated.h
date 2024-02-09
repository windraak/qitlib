
#ifndef H_AUTOSTATE_QIT
#define H_AUTOSTATE_QIT

#include "qit_statemachine.h"
#include "qit.h"

using namespace qit;

#define CreateStatemachine(WHICH, SIZE)                     \
                                                            \
StateMachine< SIZE > Statemachine;                          \
WHICH __state_init;                                         \
                                                            \
void setup() {                                              \
    Serial.begin(9600);                                     \
    while (!Serial);                                        \
    SensorServer::initialize();                             \
    Serial.println("Initialized sensors.");                 \
    delay(2500);                                            \
    Statemachine.addstate(&__state_init);                   \
}                                                           \
                                                            \
void loop() {                                               \
    SensorServer::heartbeat();                              \
    Statemachine.heartbeat();                               \
}                                                           \


#endif
