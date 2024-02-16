

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

template < int NUM , unsigned long INTERVAL = 1000 >
class Temperature : public Sensor {
public:
    OneWire oneWire;
    DallasTemperature sensors;
    float lastC = 0.0f;
    unsigned int errorRead = 0;

    unsigned long next_update = ::millis() + INTERVAL;

    void initialize() {
        oneWire.begin(NUM);
        sensors.setOneWire(&oneWire);
        sensors.begin();
        sensors.requestTemperatures();
    }

    inline float read(int bus = 0) {
        float iread = sensors.getTempCByIndex(bus);
        if (iread < -35.0f) {
            errorRead++;
            return lastC;
        }
        lastC = iread;
        return iread;
    }

    void beat() {
        if (::millis() > this->next_update) {
            sensors.requestTemperatures();
            this->next_update = ::millis() + INTERVAL;
        }
    }
};

}

#endif
