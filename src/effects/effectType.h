#ifndef H_EFFECT
#define H_EFFECT

#include <Arduino.h>

class EffectType {
public:
    String name;
    byte typeValue;
    EffectType(String name, byte typeValue): name(name), typeValue(typeValue) {}
};

#endif