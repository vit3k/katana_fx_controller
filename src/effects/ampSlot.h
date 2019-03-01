#ifndef H_AMPSLOT
#define H_AMPSLOT

#include "effectSlot.h"


class AmpSlot : public EffectSlot {
private:
    byte ampBaseAddress[4] = {0x00, 0x00, 0x04, 0x20};
    EffectParam* _params[6] = {
        new EffectParam("Gain", 0, 120, 0x00, 1),
        new EffectParam("Volume", 0, 100, 0x01, 1),
        new EffectParam("Bass", -50, 50, 0x02, 1),
        new EffectParam("Middle", -50, 50, 0x03, 1),
        new EffectParam("Treble", -50, 50, 0x04, 1),
        new EffectParam("Presence", 0, 100, 0x05, 1)
    };
    String names[5] = {"Acoustic", "Clean", "Crunch", "Lead", "Brown"};
public:
    AmpSlot(): EffectSlot("Amp", 0, ampBaseAddress) {
        enabled = true;
    }
    ~AmpSlot() {
        for(byte i = 0; i < 6; i++) {
            delete _params[i];
        }
    }
    virtual void change(byte idx);
    virtual String* list();
    virtual String currentName() { return names[current]; }
    virtual EffectParam** params() { return (EffectParam**)_params; }
    virtual byte paramsCount() { return 6; }
    virtual byte effectsCount() { return 5; }

    virtual void update() {};
    virtual byte rangeSize() { return 7; }
    virtual int32_t value(EffectParam* param);
    virtual void updateParam(EffectParam* param, int32_t value);
};
#endif