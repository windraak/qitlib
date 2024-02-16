
#ifndef H_TEMP_NORM
#define H_TEMP_NORM

// ! 5 volts

namespace qit {

template < int PIN >
class AnalogTemperature {
private:
    const int B = 4275;               // B value of the thermistor
    const int R0 = 100000;            // R0 = 100k
public:
    AnalogTemperature< PIN >() { }
    float temp = 0.0f;
    float read() {
        int a = analogRead(A3);

        float R = 1023.0/a-1.0;
        R = R0*R;

        temp = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
        return temp;
    }
};

}

#endif
