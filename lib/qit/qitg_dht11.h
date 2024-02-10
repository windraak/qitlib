

#ifndef H_DHT_GROVE
#define H_DHT_GROVE

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Simple DHT11 temperature sensor
 */

#include <Arduino.h>
#include "qit_sensor.h"

namespace qit::Grove
{

template < int PIN >
class DHTSensor : public Sensor {
public:

};

}

#endif
