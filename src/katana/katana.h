#ifndef H_KATANA
#define H_KATANA

#include "midi.h"

class Katana {
private:
    Midi::Midi* midi;
    byte calculateChecksum(byte* vals, byte valsSize);
public:
    Katana(Midi::Midi* midi): midi(midi) {}
    void set(byte address[4], byte data);
    void sendCommand(byte command, byte address[4], byte data[4], byte dataSize);
    void query(byte address[4], byte size) {}
    void update();
};

#endif
