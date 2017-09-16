#ifndef H_EFFECTS
#define H_EFFECTS

#include <Arduino.h>

class EffectParam {
public:
    String name;
    int16_t minValue;
    int16_t maxValue;
    int16_t value = 0;
    uint8_t addrOffset;

    EffectParam(String name, int16_t minValue, int16_t maxValue, uint8_t addrOffset)
        : name(name), minValue(minValue), maxValue(maxValue), addrOffset(addrOffset) {}

    void setValue(int16_t value) { this->value = value; }
};

class Effect {
public:
    String name;
    uint8_t typeValue;
    uint8_t* baseAddr;
    EffectParam* params;
    uint8_t paramsCount;
    Effect(String name, uint8_t typeValue, uint8_t baseAddr[4], EffectParam* params, uint8_t paramsCount)
        : name(name), typeValue(typeValue), baseAddr(baseAddr), params(params), paramsCount(paramsCount) {}

    Effect() {}

    void retrieve() {}
};

extern uint8_t boosterParamsBaseAddr[4];
extern EffectParam boosterParams[5];

extern Effect midBoost;//("Mid Boost", 0x00, boosterParamsBaseAddr, boosterParams, 1);
extern Effect cleanBoost;//("Clean Boost", 0x01, boosterParamsBaseAddr, boosterParams, 1);
extern Effect trebleBoost; //("Treble Boost", 0x02, boosterParamsBaseAddr, boosterParams, 1);
extern Effect crunchOD; //("Crunch OD", 0x03, boosterParamsBaseAddr, boosterParams, 1);
extern Effect naturalOD; //("Natural OD", 0x04, boosterParamsBaseAddr, boosterParams, 1);
extern Effect warmOD; //("Warm OD", 0x05, boosterParamsBaseAddr, boosterParams, 1);
extern Effect fatDS; //("Fat DS", 0x06, boosterParamsBaseAddr, boosterParams, 1);

extern Effect metalDS; //("Metal DS", 0x08, boosterParamsBaseAddr, boosterParams, 1);
extern Effect octFuzz; //("Oct Fuzz", 0x09, boosterParamsBaseAddr, boosterParams, 1);
extern Effect bluesDrive; //("Blues Drive", 0x0A, boosterParamsBaseAddr, boosterParams, 1);
extern Effect overdrive; //("Overdrive", 0x0B, boosterParamsBaseAddr, boosterParams, 1);
extern Effect tScream; //("T-Scream", 0x0C, boosterParamsBaseAddr, boosterParams, 1);
extern Effect turboOD; //("Turbo OD", 0x0D, boosterParamsBaseAddr, boosterParams, 1);
extern Effect distortion; //("Distortion", 0x0E, boosterParamsBaseAddr, boosterParams, 1);
extern Effect rat; //("Rat", 0x0F, boosterParamsBaseAddr, boosterParams, 1);
extern Effect guvDS; //("Guv DS", 0x10, boosterParamsBaseAddr, boosterParams, 1);
extern Effect dstPlus; //("DST+", 0x11, boosterParamsBaseAddr, boosterParams, 1);
extern Effect metalZone; //("Metal Zone", 0x12, boosterParamsBaseAddr, boosterParams, 1);
extern Effect fuzz60s; //("'60s Fuzz'", 0x13, boosterParamsBaseAddr, boosterParams, 1);
extern Effect muffFuzz; //("Muff Fuzz", 0x14, boosterParamsBaseAddr, boosterParams, 1);

extern Effect boosterEffects[20];

class EffectSlot {
public:
    String name;
    uint8_t chainValue;
    Effect* effects;
    uint8_t effectsCount;
    uint8_t* baseAddr;

    bool enabled;
    uint8_t currentEffectIdx;

    EffectSlot(String name, uint8_t chainValue, Effect* effects, uint8_t effectsCount, uint8_t baseAddr[4])
        : name(name), chainValue(chainValue), effects(effects), effectsCount(effectsCount), baseAddr(baseAddr), currentEffectIdx(1) {}

    void retrieve() {}
    Effect* currentEffect() { return &effects[currentEffectIdx]; }
};

extern uint8_t boosterBaseAddr[4];
extern EffectSlot booster;

#endif
