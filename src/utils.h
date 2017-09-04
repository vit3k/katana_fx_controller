#ifndef H_UTILS
#define H_UTILS

#include <Arduino.h>

namespace Utils {
    void printHex(uint8_t* buffer, uint8_t size) {
        for(uint8_t i = 0; i < size; i++) {
            if (buffer[i] < 0x10) Serial.print("0");
            Serial.print(buffer[i], HEX);
            Serial.print(" ");
        }
        Serial.print("\n");
    }
}

#endif /* end of include guard: H_UTILS */
