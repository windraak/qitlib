

#ifndef H_TEMP_GROVE
#define H_TEMP_GROVE

/*
 * qit - quick interface templates
 * (CC-0) Joey Peters
 * ****************************************************************
 * Simple grove dallas temperature sensor
 */

#include <Arduino.h>
#include "qit_sensor.h"

// Should be included in the external project (the dallas library)
#include <OneWire.h>
#include <DallasTemperature.h>

namespace qit::Grove
{

template < int NUM >
class Temperature : public Sensor {
public:
    OneWire oneWire;
    DallasTemperature sensors;

    void initialize() {
        oneWire.begin(NUM);
        sensors.setOneWire(&oneWire);

        sensors.begin();
    }

    float read(int bus = 0) {
        return sensors.getTempCByIndex(bus);
    }

    void beat() {
        sensors.requestTemperatures();
    }
};

}

#endif
