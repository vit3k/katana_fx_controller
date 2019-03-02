#include "effectSlot.h"

void addOffset(byte* address, uint8_t offset, byte* result) {
    memcpy(result, address, 4);
    uint16_t lastByte = result[3];
    lastByte += offset;
    if (lastByte > 127) {
        result[2]++;
    }
    result[3] = lastByte % 128;
}

void EffectSlot::set(EffectParam* param, int32_t value, byte offset) {
    param->update(values + offset, value);
    byte addr[4];
    addOffset(baseAddr, param->addrOffset + offset, addr);
    auto unmapped = param->unmapValue(value);
    katana->set(addr, unmapped);
};
void EffectSlot::setKatana(Katana* katana) {
    this->katana = katana;
    values = katana->registerRange(baseAddr, rangeSize());
    katana->query(baseAddr, rangeSize());
}
void EffectSlot::setOnoff(byte offset) {
    byte addr[4];
    addOffset(baseAddr, offset, addr);
    if (values[offset] == 0) {
        values[offset] = 1;
    } else {
        values[offset] = 0;
    }
    katana->set(addr, values[offset]);
}