
#ifndef H_LED_QIT
#define H_LED_QIT

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Simpler LED control derived from binary component
 */

#include <Arduino.h>
#include "qit_binary_component.h"

namespace qit
{

// A led is actually just a binary pin component
template < int NUM >
using LED = BinaryComponent< NUM >;

}

#endif
