#ifndef H_EFFECTSLOT
#define H_EFFECTSLOT

#include <Arduino.h>

#include "effectParam.h"

class EffectSlot {
public:
    String name;
    byte chainValue;
    byte* baseAddr;
    bool enabled;
    byte current;

    EffectSlot(String name, byte chainValue, byte baseAddr[4])
        : name(name), chainValue(chainValue), baseAddr(baseAddr), current(1) {}

    virtual void change(byte idx) = 0;
    virtual void list(String* names, byte &namesCount) = 0;
    virtual String currentName() = 0;
    virtual void params(EffectParam** params, byte &paramsCount) = 0;
    virtual byte paramsCount() = 0;
    virtual byte effectsCount() = 0;

};

#endif