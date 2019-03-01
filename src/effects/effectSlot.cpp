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

