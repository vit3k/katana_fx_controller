#include "rotaryEncoder.h"

int32_t RotaryEncoder::delta(byte multiplier) {
    //auto read = encoder.read();
    auto read = encoder.getCount();
    auto d = ceil((read - lastRead)/4);
    int32_t step = 0;
    if (d != 0)
    {
        auto speed = constrain(tps, MIN_TPS, MAX_TPS) - MIN_TPS;
        auto sign = d > 0 ? 1 : -1;
        step = sign * (1 + abs(d) * multiplier * speed * speed * speed / ((MAX_TPS - MIN_TPS) * (MAX_TPS - MIN_TPS) * (MAX_TPS - MIN_TPS)));
        lastRead = read;
    }
    return step;
}
int32_t RotaryEncoder::delta() {
    return delta(1);
}
int32_t RotaryEncoder::value() {
    return val;
}

void RotaryEncoder::update() {
    auto current = millis();
    //val = encoder.read();
    val = encoder.getCount();
    auto dt = current - lastTpsTime;
    if (dt >= 250) {
        tps = abs((1000.f / dt) * ((val - lastTpsValue)/2));
        lastTpsValue = val;
        lastTpsTime = current;
    }
}