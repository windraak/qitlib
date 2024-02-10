
#ifndef GROVE_BUTTON_QIT
#define GROVE_BUTTON_QIT

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * A simple button template which constructs with a constant pin.
 * Interfaces with sensor. Grove doesn't use INPUT_PULLUP but is also
 * inverted when reading.
 */


#include "qit_button.h"

namespace qit::Grove
{

template < int NUM , unsigned long DEBOUNCE = 40 >
using Button = qit::Button< NUM , DEBOUNCE , false, true>;

}

#endif