#ifndef Encoder_H
#define Encoder_H

#include <Encoder.h>

class RotaryEncoder {
private:
    Encoder encoder;
    int32_t lastValue;
public:
    int32_t delta() {
        int32_t newValue = encoder.read();
        int32_t d = newValue - lastValue;
        //if (newValue != lastValue) {

        //}
        //Serial.println(d);
        if (lastValue != newValue) {
        char buf[100];
        sprintf(buf, "%ld %ld %ld", newValue, lastValue, d);
        Serial.println(buf);
        }
        lastValue = newValue;
        return d;
    }
    int32_t value() {
        return lastValue;
    }

    RotaryEncoder(uint8_t pin1, uint8_t pin2): encoder(Encoder(pin1, pin2)), lastValue(0) {}
};

#endif