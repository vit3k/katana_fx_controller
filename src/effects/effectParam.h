#ifndef H_EFFECTPARAM
#define H_EFFECTPARAM

#include <Arduino.h>

class EffectParam {
public:
    String name;
    int16_t minValue;
    int16_t maxValue;
    int16_t value = 0;
    byte addrOffset;
    byte size;
    EffectParam(String name, int16_t minValue, int16_t maxValue, byte addrOffset, byte size)
        : name(name), minValue(minValue), maxValue(maxValue), addrOffset(addrOffset), size(size) {}

    void setValue(int16_t value) { this->value = value; }
};

#endif