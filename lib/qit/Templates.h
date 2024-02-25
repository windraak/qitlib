
#ifndef H_TEMPLATES_QIT
#define H_TEMPLATES_QIT

#include "qit_button.h"
#include "qit_statemachine.h"

namespace qit {

template< int BUTTON >
void WaitForButton() {
    static qit::Button < BUTTON > waitbutton;
    waitbutton.enable();
    waitbutton.callback = [](bool pressed) {
        if (pressed) {
            self->disable();
            qit::IStateMachine::getSingleton()->exitstate();
        }
    };
    qit::IStateMachine::getSingleton()->addstate(&NothingState);
};

}

#endif

