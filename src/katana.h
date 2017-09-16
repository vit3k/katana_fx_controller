#ifndef H_KATANA
#define H_KATANA

#include "midi.h"

class Katana {
private:
    Midi::Midi* midi;
    uint8_t calculateChecksum(uint8_t* vals, uint8_t valsSize);
public:
    Katana(Midi::Midi* midi): midi(midi) {}
    void set(uint8_t address[4], uint8_t data);
    void sendCommand(uint8_t command, uint8_t address[4], uint8_t data[4], uint8_t dataSize);
    void poll();
};

#endif
