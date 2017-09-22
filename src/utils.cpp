#include "utils.h"

namespace Utils {
    void printHex(byte* buffer, byte size) {
        for(byte i = 0; i < size; i++) {
            if (buffer[i] < 0x10) Serial.print("0");
            Serial.print(buffer[i], HEX);
            Serial.print(" ");
        }
        Serial.print("\n");
    }
}
