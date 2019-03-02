#ifndef H_EFFECT
#define H_EFFECT

#include <Arduino.h>

class EffectType {
public:
    String name;
    byte typeValue;
    EffectType(String name, byte typeValue): name(name), typeValue(typeValue) {}
};

class MultiEffectType : public EffectType {
public:
    EffectParam** params;
    byte paramsCount;
    MultiEffectType(String name, byte typeValue, EffectParam** params, byte paramsCount): EffectType(name, typeValue), params(params), paramsCount(paramsCount) {}
};
#endif