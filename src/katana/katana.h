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

class Katana {
private:
    Midi::Midi* midi;
    byte calculateChecksum(byte* vals, byte valsSize);
    KatanaCallback callbacks[10];
public:
    Katana(Midi::Midi* midi): midi(midi) {}
    void set(byte address[4], byte data);
    void sendCommand(byte command, byte address[4], byte data[4], byte dataSize);
    void query(byte address[4], byte size, Callback callback);
    void update();

};

#endif
