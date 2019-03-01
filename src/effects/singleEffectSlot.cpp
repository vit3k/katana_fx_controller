#include "singleEffectSlot.h"
#include "../utils.h"

void SingleEffectSlot::change(byte idx) {
    current = idx;
    byte addr[4];
    addOffset(baseAddr, 1, addr);
    katana->set(addr, types[current]->typeValue);
}
String* SingleEffectSlot::list() {
    auto names = new String[typesCount];
    for(byte i = 0; i < typesCount; i++) {
        names[i] = String(types[i]->name);
    }
    return names;
}
String SingleEffectSlot::currentName() {
    return types[current]->name;
}
EffectParam** SingleEffectSlot::params() {
    return _params;
}

byte SingleEffectSlot::paramsCount() {
    return _paramsCount;
}
byte SingleEffectSlot::effectsCount() {
    return typesCount;
}

void SingleEffectSlot::update() {
    if (values[0] == 0) {
        enabled = false;
    }
    else if (values[0] == 1) {
        enabled = true;
    }

    if (lastTypeValue != values[1]) {
        for (byte i = 0; i < typesCount; i++) {
            if (types[i]->typeValue == values[1]) {
                current = i;
                break;
            }
        }
        lastTypeValue = values[1];
    }
}

byte SingleEffectSlot::rangeSize() {
    byte lastOffset = 0;
    byte lastSize = 0;
    for(byte i = 0; i < _paramsCount; i++) {
        if (lastOffset < _params[i]->addrOffset) {
            lastOffset = _params[i]->addrOffset;
            lastSize = _params[i]->size;
        }
    }

    return (lastOffset + lastSize + 2);
}

int SingleEffectSlot::value(EffectParam* param) {
    
    int value = values[param->addrOffset + 2];
    //Serial.printf("value.value %d\n", value);
    if (param->size == 2) {
        value |= (values[param->addrOffset + 3] << 7);
    }
    
    return param->mapValue(value);
}

void SingleEffectSlot::updateParam(EffectParam* param, int32_t value) {
    if (value < param->minValue) {
        value = param->minValue;
    }
    if (value > param->maxValue) {
        value = param->maxValue;
    }
    byte addr[4];
    addOffset(baseAddr, param->addrOffset + 2, addr);
    auto unmapped = param->unmapValue(value);
    katana->set(addr, unmapped);
    values[param->addrOffset + 2] = unmapped & 0x7F;
    if (param->size == 2) {
        values[param->addrOffset + 3] = (unmapped >> 7) & 0x7F;
    }
}