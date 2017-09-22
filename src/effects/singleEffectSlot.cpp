#include "singleEffectSlot.h"
#include "../utils.h"

void SingleEffectSlot::change(byte idx) {
    current = idx;
    byte addr[4] = {baseAddr[0], baseAddr[1], baseAddr[2], baseAddr[3] + 1};
    katana->set(addr, types[current]->typeValue);
}
String* SingleEffectSlot::list() {
    auto names = new String[typesCount];
    for(byte i = 0; i < typesCount; i++) {
        names[i] = String(types[i]->name);
    }
    return names;
}
String SingleEffectSlot::currentName() {
    return types[current]->name;
}
EffectParam** SingleEffectSlot::params() {
    return _params;
}

byte SingleEffectSlot::paramsCount() {
    return _paramsCount;
}
byte SingleEffectSlot::effectsCount() {
    return typesCount;
}

void SingleEffectSlot::update() {
/*    katana->query(baseAddr, _paramsCount + 2, Callback(this, [](void* obj, byte* data, byte size) {
        //Utils::printHex(data, size);
        auto o = (SingleEffectSlot*)obj;
        if (data[0] == 0) {
            o->enabled = false;
        }
        else if (data[0] == 1) {
            o->enabled = true;
        }
    }));*/
    //Utils::printHex(values, 0x07);
    if (values[0] == 0) {
        enabled = false;
    }
    else if (values[0] == 1) {
        enabled = true;
    }

    if (lastTypeValue != values[1]) {
        for (byte i = 0; i < typesCount; i++) {
            if (types[i]->typeValue == values[1]) {
                current = i;
                break;
            }
        }
        lastTypeValue = values[1];
    }
}

byte SingleEffectSlot::rangeSize() {
    byte lastOffset = 0;
    byte lastSize = 0;
    for(byte i = 0; i < _paramsCount; i++) {
        if (lastOffset < _params[i]->addrOffset) {
            lastOffset = _params[i]->addrOffset;
            lastSize = _params[i]->size;
        }
    }

    return (lastOffset + lastSize + 2);
}

byte SingleEffectSlot::value(byte offset) {
    return values[offset + 2];
}
