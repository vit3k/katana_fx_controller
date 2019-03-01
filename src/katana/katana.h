#ifndef H_KATANA
#define H_KATANA

#include <Arduino.h>
#include "midi.h"

class Callback {
public:
    void* obj;
    void (*callback)(void*, byte*, byte);
    Callback(void* obj, void(*callback)(void*, byte*, byte)): obj(obj), callback(callback) {}
    Callback() {};
};

class KatanaCallback {
public:
    bool free = true;
    byte addr[4];
    Callback callback;
    KatanaCallback() {};
};

class Range {
public:
    byte baseAddr[4];
    byte lastAddr[4];
    byte size;
    byte* data;
    byte* inRange(byte addr[4]);
    Range(byte baseAddr[4], byte size);
    Range() {}
};

class Katana {
private:
    Midi::Midi* midi;
    byte calculateChecksum(byte* vals, byte valsSize);
    KatanaCallback callbacks[10];
    Range ranges[10];
    byte rangeCount = 0;
public:
    Katana(Midi::Midi* midi): midi(midi) {

    }
    void init();
    void set(byte address[4], uint16_t data);
    void sendCommand(byte command, byte address[4], byte data[4], byte dataSize);
    void query(byte address[4], byte size);
    void update();
    byte* registerRange(byte baseAddr[4], byte size);
};

#endif
