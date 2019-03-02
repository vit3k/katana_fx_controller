#ifndef H_EFFECTPARAM
#define H_EFFECTPARAM

#include <Arduino.h>

class EffectParam {
public:
    String name;
    int32_t minValue = 0;
    int32_t maxValue= 100;
    int32_t val = 0;
    uint16_t addrOffset;
    byte size;
    EffectParam(String name, int32_t minValue, int32_t maxValue, uint16_t addrOffset, byte size)
        : name(name), minValue(minValue), maxValue(maxValue), addrOffset(addrOffset), size(size) {}

    int mapValue(int val) {
        return minValue + val;
    }

    uint16_t unmapValue(int val) {
        return val - minValue;
    }

    int32_t value(byte* values);
    void update(byte* values, int32_t value);
};

#endif
