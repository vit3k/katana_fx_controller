#ifndef H_EFFECTPARAM
#define H_EFFECTPARAM

#include <Arduino.h>

class EffectParam {
public:
    String name;
    int16_t minValue = 0;
    int16_t maxValue= 100;
    int16_t value = 0;
    byte addrOffset;
    byte size;
    EffectParam(String name, int16_t minValue, int16_t maxValue, byte addrOffset, byte size)
        : name(name), minValue(minValue), maxValue(maxValue), addrOffset(addrOffset), size(size) {}

    int mapValue(int value) {
        return minValue + value;
    }

    uint16_t unmapValue(int value) {
        return value - minValue;
    }
};

#endif
