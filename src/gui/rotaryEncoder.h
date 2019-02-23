#ifndef Encoder_H
#define Encoder_H

#include <Encoder.h>

class RotaryEncoder {
private:
    Encoder encoder;
    int32_t lastValue;
    unsigned long lastChange;
public:
    int32_t delta() {
        unsigned long current = millis();
        if ( (current - lastChange) > 100) {
            int32_t newValue = encoder.read();
            int32_t d = newValue - lastValue;
            if (lastValue != newValue) {
                char buf[100];
                sprintf(buf, "%ld %ld %ld", newValue, lastValue, d);
                Serial.println(buf);
            }
            lastValue = newValue;
            if (d < 0) {
                return -1;
            } else if (d > 0) {
                return 1;
            }
            return d;
        }
        return 0;
    }
    int32_t value() {
        return lastValue;
    }

    RotaryEncoder(uint8_t pin1, uint8_t pin2): encoder(Encoder(pin1, pin2)), lastValue(0), lastChange(millis()) {}
};

#endif