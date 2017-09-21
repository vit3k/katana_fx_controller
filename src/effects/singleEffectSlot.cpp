#include "singleEffectSlot.h"
#include "../utils.h"

void SingleEffectSlot::change(byte idx) {
    current = idx;
}
void SingleEffectSlot::list(String* names, byte &namesCount) {
    names = new String[typesCount];
    for(byte i = 0; i < typesCount; i++) {
        names[i] = types[i]->name;
    }
    namesCount = typesCount;
}
String SingleEffectSlot::currentName() {
    return types[current]->name;
}
void SingleEffectSlot::params(EffectParam** params, byte &paramsCount) {
    params = _params;
    paramsCount = _paramsCount;
}

byte SingleEffectSlot::paramsCount() {
    return _paramsCount;
}
byte SingleEffectSlot::effectsCount() {
    return typesCount;
}

void SingleEffectSlot::retrieve() {
    katana->query(baseAddr, _paramsCount + 2, Callback(this, [](void* obj, byte* data, byte size) {
        //Utils::printHex(data, size);
        auto o = (SingleEffectSlot*)obj;
        if (data[0] == 0) {
            o->enabled = false;
        }
        else if (data[0] == 1) {
            o->enabled = true;
        }
    }));
}
