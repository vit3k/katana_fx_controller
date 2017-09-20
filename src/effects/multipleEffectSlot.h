#ifndef H_MULTIPLE_EFFECT_SLOT
#define H_MULTIPLE_EFFECT_SLOT

/*
class MultipleEffectSlot : public EffectSlot {
public:
    Effect** effects;
    byte effectCount;

    MultipleEffectSlot(String name, byte chainValue, byte baseAddr[4], Effect** effects, byte effectCount)
        : EffectSlot(name, chainValue, baseAddr), effects(effects), effectCount(effectCount) {}

    void change(byte idx);
    void list(String* names, byte &namesCount);
    String currentName();
    void params(EffectParam* params, byte &paramsCount);
    byte paramsCount();
    byte effectsCount();
};*/

//extern byte boosterParamsBaseAddr[4];
//extern EffectParam* boosterParams[5];

/*extern Effect midBoost;//("Mid Boost", 0x00, boosterParamsBaseAddr, boosterParams, 1);
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

extern Effect* boosterEffects[20];
*/



/*

EffectParam boosterParams[BOOSTER_PARAMS_COUNT] = {
    EffectParam("Drive", 0, 100, 0x00, 1),
    EffectParam("Tone", -50, 50, 0x02, 1),
    EffectParam("Level", 0, 100, 0x05, 1),
    EffectParam("Bottom", -50, 50, 0x01, 1),
    EffectParam("Direct Mix", -0, 100, 0x06, 1),
};


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
*/
/*byte boosterBaseAddr[4] = {0x60, 0x00, 0x00, 0x30};
SingleEffectSlot booster("Booster", 0x0F, boosterBaseAddr, boosterEffectTypes, BOOSTER_EFFECTS_COUNT, boosterParams, BOOSTER_PARAMS_COUNT);
*/

#endif