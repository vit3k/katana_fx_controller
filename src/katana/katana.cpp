#include "katana.h"

byte Katana::calculateChecksum(byte* vals, byte valsSize)
{
    byte acc = 0;
    for(byte i = 0; i < valsSize; i++)
    {
        acc += vals[i] & 0x7F;
    }

    return (128 - acc) & 0x7F;
}
void Katana::sendCommand(byte command, byte address[4], byte data[4], byte dataSize)
{
    byte rawData[8] = {address[0], address[1], address[2], address[3]};
    for(byte i = 0; i < dataSize; i++)
    {
        rawData[4 + i] = data[i];
    }
    byte size = 4 + dataSize;
    byte sysexData[20] = {0xF0, 0x41, 0x00, 0x00, 0x00, 0x00, 0x33, command};
    memcpy(sysexData + 8, rawData, size);
    sysexData[8 + size] = calculateChecksum(rawData, size);
    sysexData[8 + size + 1] = 0xF7;

    Midi::SysExMessage msg = Midi::SysExMessage(sysexData, 9 + size);
    midi->send(msg);
}
void Katana::set(byte address[4], byte data)
{
    byte rawData[1] = {data};
    sendCommand(0x12, address, rawData, 1);
}

void Katana::update() {
    midi->update(); // update MIDI interface and queues
    Midi::Message msg;
    while(midi->receive(&msg) != 0) {
        
    }
     
}
