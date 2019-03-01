#include "effectParam.h"

int32_t EffectParam::value(byte* values) {
    int value = values[addrOffset];
    if (size == 2) {
        value |= (values[addrOffset + 1] << 7);
    }
    return mapValue(value);
}

void EffectParam::update(byte* values, int32_t value) {
    if (value < minValue) {
        value = minValue;
    }
    if (value > maxValue) {
        value = maxValue;
    }
    byte addr[4];
    //addOffset(baseAddr, param->addrOffset + 2, addr);
    auto unmapped = unmapValue(value);
    //katana->set(addr, unmapped);
    values[addrOffset] = unmapped & 0x7F;
    if (size == 2) {
        values[addrOffset + 1] = (unmapped >> 7) & 0x7F;
    }
}