
#ifndef H_TEMPLATES_QIT_GROVEB
#define H_TEMPLATES_QIT_GROVEB

#include "qitg_button.h"
#include "qit_statemachine.h"

namespace qit {

template< int BUTTON >
void WaitForGroveButton() {
    static qit::Grove::Button < BUTTON > waitbutton;
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

