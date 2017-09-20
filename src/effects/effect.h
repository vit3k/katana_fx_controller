#ifndef H_EFFECT
#define H_EFFECT

class Effect {
public:
    String name;
    byte typeValue;
    byte* baseAddr;
    byte* lastAddr;
    EffectParam* params;
    byte paramsCount;
    Effect(String name, byte typeValue, byte baseAddr[4], EffectParam* params, byte paramsCount)
        : name(name), typeValue(typeValue), baseAddr(baseAddr), params(params), paramsCount(paramsCount) {
    }

    Effect() {}

    void retrieve() {}
};

#endif