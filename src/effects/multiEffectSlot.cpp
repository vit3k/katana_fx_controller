#include "multiEffectSlot.h"
#include "../utils.h"

void MultiEffectSlot::change(byte idx) {
    current = idx;
    byte addr[4];
    addOffset(baseAddr, 1, addr);
    katana->set(addr, effects[current]->typeValue);
}
String* MultiEffectSlot::list() {
    auto names = new String[_effectsCount];
    for(byte i = 0; i < _effectsCount; i++) {
        names[i] = String(effects[i]->name);
    }
    return names;
}
String MultiEffectSlot::currentName() {
    return effects[current]->name;
}
EffectParam** MultiEffectSlot::params() {
    return effects[current]->params;
}

byte MultiEffectSlot::paramsCount() {
    return effects[current]->paramsCount;
}
byte MultiEffectSlot::effectsCount() {
    return _effectsCount;
}

void MultiEffectSlot::update() {
    if (values[0] == 0) {
        enabled = false;
    }
    else if (values[0] == 1) {
        enabled = true;
    }

    if (lastTypeValue != values[1]) {
        for (byte i = 0; i < _effectsCount; i++) {
            if (effects[i]->typeValue == values[1]) {
                current = i;
                break;
            }
        }
        lastTypeValue = values[1];
    }
}

byte MultiEffectSlot::rangeSize() {
    byte lastOffset = 0;
    byte lastSize = 0;
    for(byte i = 0; i < _effectsCount; i++) {
        for(byte j = 0; j < effects[i]->paramsCount; j++) {
            if (lastOffset < effects[i]->params[j]->addrOffset) {
                lastOffset = effects[i]->params[j]->addrOffset;
                lastSize = effects[i]->params[j]->size;
            }
        }
    }
    return (lastOffset + lastSize + 2);
}

int32_t MultiEffectSlot::value(EffectParam* param) {
    return param->value(values + 2);
}
void MultiEffectSlot::updateParam(EffectParam* param, int32_t value) {
    set(param, value, 2);
}