#ifndef H_SINGLEEFFECTSLOT
#define H_SINGLEEFFECTSLOT

#include <Arduino.h>
#include "effectSlot.h"
#include "effectType.h"
#include "effectParam.h"
#include "../katana/katana.h"

class SingleEffectSlot;

class SingleEffectSlot : public EffectSlot {
public:
    EffectType** types;
    byte typesCount;
    EffectParam** _params;
    byte _paramsCount;
    byte lastTypeValue;

    SingleEffectSlot(String name, byte chainValue, byte baseAddr[4], EffectType** types, byte typesCount, EffectParam** params, byte paramsCount)
        : EffectSlot(name, chainValue, baseAddr), types(types), typesCount(typesCount), _params(params), _paramsCount(paramsCount) {
            lastTypeValue = types[current]->typeValue;
        }

    void change(byte idx);
    String* list();
    String currentName();
    EffectParam** params();
    byte paramsCount();
    byte effectsCount();
    byte rangeSize();
    byte value(byte offset);
    void update();
};

#endif
