#include "multipleEffectSlot.h"

/*
Effect* allEffects[20] = {
    &midBoost, &cleanBoost, &trebleBoost, &crunchOD, &naturalOD, &warmOD, &fatDS, &metalDS, &octFuzz, &bluesDrive, &overdrive,
    &tScream, &turboOD, &distortion, &rat, &guvDS, &dstPlus, &metalZone, &fuzz60s, &muffFuzz
};
*/
/*
void MultipleEffectSlot::change(byte idx) {
    //byte typeAddr[4] = {baseAddr[0], baseAddr[1], baseAddr[2], baseAddr[3] + 1};
    current = idx;
}
void MultipleEffectSlot::list(String* names, byte &namesCount) {
    names = new String[effectCount];
    for(byte i = 0; i < effectCount; i++) {
        names[i] = effects[i]->name;
    }
    namesCount = effectCount;
}
String MultipleEffectSlot::currentName() {
    return effects[current]->name;
}
void MultipleEffectSlot::params(EffectParam** params, byte &paramsCount) {
    params = effects[current]->params;
    paramsCount = effects[current]->paramsCount;
}
byte MultipleEffectSlot::paramsCount() {
    return effects[current]->paramsCount;
}
byte MultipleEffectSlot::effectsCount() {
    return effectCount;
}
*/

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