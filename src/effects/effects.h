#ifndef H_EFFECTS
#define H_EFFECTS

#include <Arduino.h>
#include "effectParam.h"
#include "effectType.h"
#include "singleEffectSlot.h"

#define BOOSTER_EFFECTS_COUNT 20
#define BOOSTER_PARAMS_COUNT 5
#define SLOTS_COUNT 1

class Effects {
private:
    byte boosterParamsBaseAddr[4] = {0x60, 0x00, 0x00, 0x32};
    byte boosterBaseAddr[4] = {0x60, 0x00, 0x00, 0x30};

    EffectParam* boosterParams[BOOSTER_PARAMS_COUNT] = {
        new EffectParam("Drive", 0, 100, 0x00, 1),
        new EffectParam("Tone", -50, 50, 0x02, 1),
        new EffectParam("Level", 0, 100, 0x05, 1),
        new EffectParam("Bottom", -50, 50, 0x01, 1),
        new EffectParam("Direct Mix", -0, 100, 0x06, 1)
    };

    EffectType* boosterEffectTypes[BOOSTER_EFFECTS_COUNT] =
    {
        new EffectType("Mid Boost", 0x00),
        new EffectType("Clean Boost", 0x01),
        new EffectType("Treble Boost", 0x02),
        new EffectType("Crunch OD", 0x03),
        new EffectType("Natural OD", 0x04),
        new EffectType("Warm OD", 0x05),
        new EffectType("Fat DS", 0x06),
        new EffectType("Metal DS", 0x08),
        new EffectType("Oct Fuzz", 0x09),
        new EffectType("Blues Drive", 0x0A),
        new EffectType("Overdrive", 0x0B),
        new EffectType("T-Scream", 0x0C),
        new EffectType("Turbo OD", 0x0D),
        new EffectType("Distortion", 0x0E),
        new EffectType("Rat", 0x0F),
        new EffectType("Guv DS", 0x10),
        new EffectType("DST+", 0x11),
        new EffectType("Metal Zone", 0x12),
        new EffectType("'60s Fuzz'", 0x13),
        new EffectType("Muff Fuzz", 0x14)
    };

public:
    EffectSlot* slots[SLOTS_COUNT] = {
        new SingleEffectSlot("Booster", 0x0F, boosterBaseAddr, boosterEffectTypes, BOOSTER_EFFECTS_COUNT, boosterParams, BOOSTER_PARAMS_COUNT)
    };

    Effects(Katana* katana) {

        for(byte i = 0; i < SLOTS_COUNT; i++) {
            auto slot = (SingleEffectSlot*)slots[i];
            Serial.println(slot->name);
            for(byte j = 0; j < slot->_paramsCount; j++) {
                Serial.println(slot->_params[j]->name);
            }
        }
        for(byte i = 0; i < SLOTS_COUNT; i++) {
            slots[i]->setKatana(katana);
        }
    }

    ~Effects() {
        //delete[] boosterEffectTypes;
        //delete[] boosterParams;
    }
};
#endif
