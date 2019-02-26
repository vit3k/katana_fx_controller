#ifndef Encoder_H
#define Encoder_H

#include <Encoder.h>
#define MIN_TPS 5
#define MAX_TPS 15

class RotaryEncoder {
private:
    Encoder encoder;
    int32_t lastRead;
    int32_t val;
    float tps;
    int32_t lastTpsValue;
    unsigned long lastTpsTime;
    byte multiplier;
public:
    int32_t delta() {
        auto read = encoder.read();
        auto d = ceil((read - lastRead)/4);
        int32_t step = 0;
        if (d != 0)
        {
            auto speed = constrain(tps, MIN_TPS, MAX_TPS) - MIN_TPS;
            auto sign = d > 0 ? 1 : -1;
            step = sign * (1 + abs(d) * multiplier * speed * speed * speed / ((MAX_TPS - MIN_TPS) * (MAX_TPS - MIN_TPS) * (MAX_TPS - MIN_TPS)));
            Serial.printf("%f %d\n", speed, step);
            lastRead = read;
        }
        return step;
    }
    int32_t value() {
        return val;
    }
    void setMultiplier(byte m) {
        multiplier = m;
    }

    void update() {
        auto current = millis();
        val = encoder.read();
        auto dt = current - lastTpsTime;
        if (dt >= 250) {
            tps = abs((1000.f / dt) * ((val - lastTpsValue)/2));
            lastTpsValue = val;
            lastTpsTime = current;
        }
    }

    RotaryEncoder(uint8_t pin1, uint8_t pin2): encoder(Encoder(pin1, pin2)),
        lastRead(0), tps(0), lastTpsValue(0), lastTpsTime(millis()), multiplier(4) {}
};

#endif