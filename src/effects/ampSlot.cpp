#include "ampSlot.h"

void AmpSlot::change(byte idx) {
    current = idx;
    katana->set(baseAddr, idx);
}

int32_t AmpSlot::value(EffectParam* param) {
    return param->value(values + 1);
}
void AmpSlot::updateParam(EffectParam* param, int32_t value) {
    set(param, value, 1);
}

String* AmpSlot::list() {
    auto copy = new String[5];
    for(byte i = 0; i < 5; i++) {
        copy[i] = String(names[i]);
    }
    return copy;
}