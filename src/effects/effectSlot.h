#ifndef H_EFFECTSLOT
#define H_EFFECTSLOT

#include <Arduino.h>

#include "effectParam.h"
#include "../katana/katana.h"

void addOffset(byte* address, uint8_t offset, byte* result);

class EffectSlot {
public:
    String name;
    byte chainValue;
    byte* baseAddr;
    bool enabled;
    byte current;
    Katana* katana;
    byte* values;
    EffectSlot(String name, byte chainValue, byte baseAddr[4])
        : name(name), chainValue(chainValue), baseAddr(baseAddr), current(0) {}

    virtual void change(byte idx) = 0;
    virtual String* list() = 0;
    virtual String currentName() = 0;
    virtual EffectParam** params() = 0;
    virtual byte paramsCount() = 0;
    virtual byte effectsCount() = 0;

    virtual void update() = 0;
    virtual byte rangeSize() = 0;
    virtual byte value(byte offset) = 0;
    virtual void updateParam(EffectParam* param, int32_t value) = 0;
    void setKatana(Katana* katana) {
        this->katana = katana;
        values = katana->registerRange(baseAddr, rangeSize());
        katana->query(baseAddr, rangeSize());
    }
};

#endif
