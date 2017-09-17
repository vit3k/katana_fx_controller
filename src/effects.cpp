#include "effects.h"

#define BOOSTER_EFFECTS_COUNT 20
#define BOOSTER_PARAMS_COUNT 5
uint8_t boosterParamsBaseAddr[4] = {0x60, 0x00, 0x00, 0x32};

EffectParam boosterParams[BOOSTER_PARAMS_COUNT] = {
    EffectParam("Drive", 0, 100, 0x00, 1),
    EffectParam("Tone", -50, 50, 0x02, 1),
    EffectParam("Level", 0, 100, 0x05, 1),
    EffectParam("Bottom", -50, 50, 0x01, 1),
    EffectParam("Direct Mix", -0, 100, 0x06, 1),
};

/*
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

Effect* boosterEffects[20] = {
    &midBoost, &cleanBoost, &trebleBoost, &crunchOD, &naturalOD, &warmOD, &fatDS, &metalDS, &octFuzz, &bluesDrive, &overdrive,
    &tScream, &turboOD, &distortion, &rat, &guvDS, &dstPlus, &metalZone, &fuzz60s, &muffFuzz
};
*/
EffectType midBoost("Mid Boost", 0x00);
EffectType cleanBoost("Clean Boost", 0x01);
EffectType trebleBoost("Treble Boost", 0x02);
EffectType crunchOd("Crunch OD", 0x03);
EffectType naturalOd("Natural OD", 0x04);
EffectType warmOd("Warm OD", 0x05);
EffectType fatDs("Fat DS", 0x06);
EffectType metalDs("Metal DS", 0x08);
EffectType octFuzz("Oct Fuzz", 0x09);
EffectType bluesDrive("Blues Drive", 0x0A);
EffectType overdrive("Overdrive", 0x0B);
EffectType tScream("T-Scream", 0x0C);
EffectType turboOd("Turbo OD", 0x0D);
EffectType distortion("Distortion", 0x0E);
EffectType rat("Rat", 0x0F);
EffectType guvDs("Guv DS", 0x10);
EffectType dstPlus("DST+", 0x11);
EffectType metalZone("Metal Zone", 0x12);
EffectType fuzz60s("'60s Fuzz'", 0x13);
EffectType muffFuzz("Muff Fuzz", 0x14);

EffectType* boosterEffectTypes[BOOSTER_EFFECTS_COUNT] = {&midBoost, &cleanBoost, &trebleBoost, &crunchOd,
    &naturalOd, &warmOd, &fatDs, &metalDs, &octFuzz, &bluesDrive, &overdrive, &tScream, &turboOd, &distortion,
    &rat, &guvDs, &dstPlus, &metalZone, &fuzz60s, &muffFuzz};

uint8_t boosterBaseAddr[4] = {0x60, 0x00, 0x00, 0x30};
SingleEffectSlot booster("Booster", 0x0F, boosterBaseAddr, boosterEffectTypes, BOOSTER_EFFECTS_COUNT, boosterParams, BOOSTER_PARAMS_COUNT);

/*
Effect* allEffects[20] = {
    &midBoost, &cleanBoost, &trebleBoost, &crunchOD, &naturalOD, &warmOD, &fatDS, &metalDS, &octFuzz, &bluesDrive, &overdrive,
    &tScream, &turboOD, &distortion, &rat, &guvDS, &dstPlus, &metalZone, &fuzz60s, &muffFuzz
};
*/
/*
void MultipleEffectSlot::change(uint8_t idx) {
    //uint8_t typeAddr[4] = {baseAddr[0], baseAddr[1], baseAddr[2], baseAddr[3] + 1};
    current = idx;
}
void MultipleEffectSlot::list(String* names, uint8_t &namesCount) {
    names = new String[effectCount];
    for(uint8_t i = 0; i < effectCount; i++) {
        names[i] = effects[i]->name;
    }
    namesCount = effectCount;
}
String MultipleEffectSlot::currentName() {
    return effects[current]->name;
}
void MultipleEffectSlot::params(EffectParam** params, uint8_t &paramsCount) {
    params = effects[current]->params;
    paramsCount = effects[current]->paramsCount;
}
uint8_t MultipleEffectSlot::paramsCount() {
    return effects[current]->paramsCount;
}
uint8_t MultipleEffectSlot::effectsCount() {
    return effectCount;
}
*/
void SingleEffectSlot::change(uint8_t idx) {
    current = idx;
}
void SingleEffectSlot::list(String* names, uint8_t &namesCount) {
    names = new String[typesCount];
    for(uint8_t i = 0; i < typesCount; i++) {
        names[i] = types[i]->name;
    }
    namesCount = typesCount;
}
String SingleEffectSlot::currentName() {
    return types[current]->name;
}
void SingleEffectSlot::params(EffectParam* params, uint8_t &paramsCount) {
    params = _params;
    paramsCount = _paramsCount;
}

uint8_t SingleEffectSlot::paramsCount() {
    return _paramsCount;
}
uint8_t SingleEffectSlot::effectsCount() {
    return typesCount;
}
