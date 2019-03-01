#ifndef H_NOISEGATESLOT
#define H_NOISEGATESLOT

#include "effectSlot.h"

class NoiseGateSlot : public EffectSlot {
private:
    byte ngBaseAddress[4] = {0x60, 0x00, 0x06, 0x63};
    EffectParam* _params[6] = {
        new EffectParam("Thresh", 0, 100, 0x00, 1),
        new EffectParam("Release", 0, 100, 0x01, 1),
    };
public:
    NoiseGateSlot(): EffectSlot("Noise gate", 0, ngBaseAddress) {}
    ~NoiseGateSlot() {
        for(byte i = 0; i < 6; i++) {
            delete _params[i];
        }
    }
    virtual void change(byte idx) {}
    virtual String* list() { return nullptr; }
    virtual String currentName() { return ""; }
    virtual EffectParam** params() { return (EffectParam**)_params; }
    virtual byte paramsCount() { return 2; }
    virtual byte effectsCount() { return 1; }

    virtual void update() {};
    virtual byte rangeSize() { return 3; }
    virtual int32_t value(EffectParam* param) { return param->value(values + 1); }
    virtual void updateParam(EffectParam* param, int32_t value) { set(param, value, 1 );}
    void onoff() { setOnoff(0); }
};

#endif