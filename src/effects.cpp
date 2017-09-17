#include "effects.h"

uint8_t boosterParamsBaseAddr[4] = {0x60, 0x00, 0x00, 0x32};
EffectParam boosterParams[5] = {
    EffectParam("Drive", 0, 100, 0x00),
    EffectParam("Tone", -50, 50, 0x02),
    EffectParam("Level", 0, 100, 0x05),
    EffectParam("Bottom", -50, 50, 0x01),
    EffectParam("Direct Mix", -0, 100, 0x06),
};

Effect midBoost("Mid Boost", 0x00, boosterParamsBaseAddr, boosterParams, 5);
Effect cleanBoost("Clean Boost", 0x01, boosterParamsBaseAddr, boosterParams, 5);
Effect trebleBoost("Treble Boost", 0x02, boosterParamsBaseAddr, boosterParams, 5);
Effect crunchOD("Crunch OD", 0x03, boosterParamsBaseAddr, boosterParams, 5);
Effect naturalOD("Natural OD", 0x04, boosterParamsBaseAddr, boosterParams, 5);
Effect warmOD("Warm OD", 0x05, boosterParamsBaseAddr, boosterParams, 5);
Effect fatDS("Fat DS", 0x06, boosterParamsBaseAddr, boosterParams, 5);

Effect metalDS("Metal DS", 0x08, boosterParamsBaseAddr, boosterParams, 5);
Effect octFuzz("Oct Fuzz", 0x09, boosterParamsBaseAddr, boosterParams, 5);
Effect bluesDrive("Blues Drive", 0x0A, boosterParamsBaseAddr, boosterParams, 5);
Effect overdrive("Overdrive", 0x0B, boosterParamsBaseAddr, boosterParams, 5);
Effect tScream("T-Scream", 0x0C, boosterParamsBaseAddr, boosterParams, 5);
Effect turboOD("Turbo OD", 0x0D, boosterParamsBaseAddr, boosterParams, 5);
Effect distortion("Distortion", 0x0E, boosterParamsBaseAddr, boosterParams, 5);
Effect rat("Rat", 0x0F, boosterParamsBaseAddr, boosterParams, 5);
Effect guvDS("Guv DS", 0x10, boosterParamsBaseAddr, boosterParams, 5);
Effect dstPlus("DST+", 0x11, boosterParamsBaseAddr, boosterParams, 5);
Effect metalZone("Metal Zone", 0x12, boosterParamsBaseAddr, boosterParams, 5);
Effect fuzz60s("'60s Fuzz'", 0x13, boosterParamsBaseAddr, boosterParams, 5);
Effect muffFuzz("Muff Fuzz", 0x14, boosterParamsBaseAddr, boosterParams, 5);

Effect boosterEffects[20] = {midBoost, cleanBoost, trebleBoost, crunchOD, naturalOD, warmOD, fatDS, metalDS, octFuzz, bluesDrive, overdrive,
                            tScream, turboOD, distortion, rat, guvDS, dstPlus, metalZone, fuzz60s, muffFuzz};

uint8_t boosterBaseAddr[4] = {0x60, 0x00, 0x00, 0x30};
EffectSlot booster("Booster", 0x0F, boosterEffects, 20, boosterBaseAddr);

void EffectSlot::changeEffect(uint8_t effectIdx) {
    uint8_t typeAddr[4] = {baseAddr[0], baseAddr[1], baseAddr[2], baseAddr[3] + 1};
    currentEffectIdx = effectIdx;
}
