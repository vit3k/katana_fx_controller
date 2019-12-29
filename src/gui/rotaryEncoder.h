#ifndef Encoder_H
#define Encoder_H

//#include <Encoder.h>
#include <ESP32Encoder.h>
#define MIN_TPS 5
#define MAX_TPS 15

class RotaryEncoder {
private:
    //Encoder encoder;
    ESP32Encoder encoder;
    int32_t lastRead;
    int32_t val;
    float tps;
    int32_t lastTpsValue;
    unsigned long lastTpsTime;
public:
    int32_t delta(byte multiplier);
    int32_t delta();
    int32_t value();
    void update();

    RotaryEncoder(uint8_t pin1, uint8_t pin2): //encoder(Encoder(pin1, pin2)),
        lastRead(0), tps(0), lastTpsValue(0), lastTpsTime(millis()) {
        ESP32Encoder::useInternalWeakPullResistors=true;
	    encoder.clearCount();
        encoder.attachHalfQuad(pin1, pin2);

    }
};

#endif