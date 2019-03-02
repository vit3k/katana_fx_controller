#ifndef H_MULTIEFFECTSLOT
#define H_MULTIEFFECTSLOT

#include <Arduino.h>
#include "effectSlot.h"
#include "effectType.h"
#include "effectParam.h"
#include "../katana/katana.h"

class MultiEffectSlot : public EffectSlot {
public:
    MultiEffectType** effects;
    byte _effectsCount;
    byte lastTypeValue;

    MultiEffectSlot(String name, byte chainValue, byte baseAddr[4], MultiEffectType** effects, byte _effectsCount)
        : EffectSlot(name, chainValue, baseAddr), effects(effects), _effectsCount(_effectsCount) {}

    void change(byte idx);
    String* list();
    String currentName();
    EffectParam** params();
    byte paramsCount();
    byte effectsCount();
    byte rangeSize();
    void update();
    int32_t value(EffectParam* param);
    virtual void updateParam(EffectParam* param, int32_t value);
    void onoff() { setOnoff(0); }
};

#endif
