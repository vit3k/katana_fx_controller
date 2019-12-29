#ifndef H_EFFECTS
#define H_EFFECTS

#include <Arduino.h>
#include "effectParam.h"
#include "effectType.h"
#include "singleEffectSlot.h"
#include "ampSlot.h"
#include "noiseGateSlot.h"
#include "multiEffectSlot.h"

#define BOOSTER_EFFECTS_COUNT 20
#define BOOSTER_PARAMS_COUNT 5
#define DELAY_PARAMS_COUNT 7
#define DELAY_EFFECTS_COUNT 6
#define REVERB_PARAMS_COUNT 8
#define REVERB_EFFECTS_COUNT 7
#define SLOTS_COUNT 8
#define EFFECTS_COUNT 2

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
        new EffectType("Ambience", 0x00),
        new EffectType("Room", 0x01),
        new EffectType("Hall 1", 0x02),
        new EffectType("Hall 2", 0x03),
        new EffectType("Plate", 0x04),
        new EffectType("Spring", 0x05),
        new EffectType("Modulate", 0x06),
    };

    EffectParam* chorusParams[1] = {
        new EffectParam("Rate", 0, 100, 0xF8, 1),
    };
    EffectParam* tremoloParams[4] = {
        new EffectParam("Shape", 0, 100, 0xC5, 1),
        new EffectParam("Rate", 0, 100, 0xC6, 1),
        new EffectParam("Depth", 0, 100, 0xC7, 1),
        new EffectParam("Level", 0, 100, 0xC8, 1)
    };
    MultiEffectType* effects[EFFECTS_COUNT] = {
        new MultiEffectType("Chorus", 0x1D, chorusParams, 1),
        new MultiEffectType("Tremolo", 0x15, tremoloParams, 4)
    };

    byte modBaseAddr[4] = {0x60, 0x00, 0x01, 0x40};
    byte fxBaseAddr[4] = {0x60, 0x00, 0x03, 0x4C};
public:
    EffectSlot* slots[SLOTS_COUNT] = {
        new NoiseGateSlot(),
        new SingleEffectSlot("Booster", 0x0F, boosterBaseAddr, boosterEffectTypes, BOOSTER_EFFECTS_COUNT, boosterParams, BOOSTER_PARAMS_COUNT),
        new MultiEffectSlot("Mod", 0x00, modBaseAddr, effects, EFFECTS_COUNT),
        new AmpSlot(),
        new SingleEffectSlot("Delay", 0x00, delayBaseAddr, delayEffectTypes, DELAY_EFFECTS_COUNT, delayParams, DELAY_PARAMS_COUNT),
        new MultiEffectSlot("FX", 0x00, fxBaseAddr, effects, EFFECTS_COUNT),
        new SingleEffectSlot("Delay 2", 0x00, delay2BaseAddr, delayEffectTypes, DELAY_EFFECTS_COUNT, delayParams, DELAY_PARAMS_COUNT),
        new SingleEffectSlot("Reverb", 0x00, reverbBaseAddr, reverbEffectTypes, REVERB_EFFECTS_COUNT, reverbParams, REVERB_PARAMS_COUNT),
    };
// eq 01 30
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
