#ifndef H_EFFECTS
#define H_EFFECTS

#include <Arduino.h>
#include "effectParam.h"
#include "effectType.h"
#include "singleEffectSlot.h"
#include "ampSlot.h"
#include "noiseGateSlot.h"

#define BOOSTER_EFFECTS_COUNT 20
#define BOOSTER_PARAMS_COUNT 5
#define DELAY_PARAMS_COUNT 7
#define DELAY_EFFECTS_COUNT 6
#define REVERB_PARAMS_COUNT 8
#define REVERB_EFFECTS_COUNT 5
#define SLOTS_COUNT 6

class Effects {
private:
    byte boosterParamsBaseAddr[4] = {0x60, 0x00, 0x00, 0x32};
    byte boosterBaseAddr[4] = {0x60, 0x00, 0x00, 0x30};

    EffectParam* boosterParams[BOOSTER_PARAMS_COUNT] = {
        new EffectParam("Drive", 0, 100, 0x00, 1),
        new EffectParam("Tone", -50, 50, 0x02, 1),
        new EffectParam("Level", 0, 100, 0x05, 1),
        new EffectParam("Bottom", -50, 50, 0x01, 1),
        new EffectParam("D Mix", -0, 100, 0x06, 1)
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

    byte delayBaseAddr[4] = {0x60, 0x00, 0x05, 0x60};
    byte delay2BaseAddr[4] = {0x60, 0x00, 0x10, 0x4E};

    EffectParam* delayParams[DELAY_PARAMS_COUNT] = {
        new EffectParam("Time", 0, 2000, 0x00, 2),
        new EffectParam("Feedback", 0, 100, 0x02, 1),
        new EffectParam("Level", 0, 120, 0x04, 1),
        new EffectParam("H Cut", 0, 15, 0x03, 1),
        new EffectParam("D Mix", 0, 100, 0x05, 1),
        new EffectParam("M Depth", 0, 100, 18, 1),
        new EffectParam("M Rate", 0, 100, 17, 1)
    };

    EffectType* delayEffectTypes[DELAY_EFFECTS_COUNT] =
    {
        new EffectType("Digital", 0x00),
        new EffectType("Reverse", 0x06),
        new EffectType("Analog", 0x07),
        new EffectType("Tape Echo", 0x08),
        new EffectType("Modulate", 0x09),
        new EffectType("SDE-3000", 0x0A)
    };

    byte reverbBaseAddr[4] = {0x60, 0x00, 0x06, 0x10};

    EffectParam* reverbParams[REVERB_PARAMS_COUNT] = {
        new EffectParam("Time", 0, 99, 0x00, 1),
        new EffectParam("Density", 0, 10, 0x05, 1),
        new EffectParam("Level", 0, 100, 0x06, 1),
        new EffectParam("D Mix", 0, 100, 0x06, 1),
        new EffectParam("Pre-d", 0, 500, 0x01, 2),
        new EffectParam("L cut", 0, 0x11, 0x03, 1),
        new EffectParam("H cut", 0, 15, 0x04, 1),
        new EffectParam("Spr Sen", 0, 100, 0x07, 1)
    };
    EffectType* reverbEffectTypes[REVERB_EFFECTS_COUNT] =
    {
        new EffectType("Room", 0x01),
        new EffectType("Hall", 0x03),
        new EffectType("Plate", 0x04),
        new EffectType("Sprint", 0x05),
        new EffectType("Modulate", 0x06),
    };
public:
    EffectSlot* slots[SLOTS_COUNT] = {
        new NoiseGateSlot(),
        new SingleEffectSlot("Booster", 0x0F, boosterBaseAddr, boosterEffectTypes, BOOSTER_EFFECTS_COUNT, boosterParams, BOOSTER_PARAMS_COUNT),
        new AmpSlot(),
        new SingleEffectSlot("Delay", 0x00, delayBaseAddr, delayEffectTypes, DELAY_EFFECTS_COUNT, delayParams, DELAY_PARAMS_COUNT),
        new SingleEffectSlot("Delay 2", 0x00, delay2BaseAddr, delayEffectTypes, DELAY_EFFECTS_COUNT, delayParams, DELAY_PARAMS_COUNT),
        new SingleEffectSlot("Reverb", 0x00, reverbBaseAddr, reverbEffectTypes, REVERB_EFFECTS_COUNT, reverbParams, REVERB_PARAMS_COUNT),
    };

    Effects(Katana* katana) {
        for(byte i = 0; i < SLOTS_COUNT; i++) {
            slots[i]->setKatana(katana);
        }
    }

    ~Effects() {
    }

    void update() {
        for(byte i = 0; i < SLOTS_COUNT; i++) {
            slots[i]->update();
        }
    }
};
#endif
