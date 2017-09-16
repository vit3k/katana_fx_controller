#include "katana.h"

uint8_t Katana::calculateChecksum(uint8_t* vals, uint8_t valsSize)
{
    uint8_t acc = 0;
    for(uint8_t i = 0; i < valsSize; i++)
    {
        acc += vals[i] & 0x7F;
    }

    return (128 - acc) & 0x7F;
}
void Katana::sendCommand(uint8_t command, uint8_t address[4], uint8_t data[4], uint8_t dataSize)
{
    uint8_t rawData[8] = {address[0], address[1], address[2], address[3]};
    for(uint8_t i = 0; i < dataSize; i++)
    {
        rawData[4 + i] = data[i];
    }
    uint8_t size = 4 + dataSize;
    uint8_t sysexData[20] = {0xF0, 0x41, 0x00, 0x00, 0x00, 0x00, 0x33, command};
    memcpy(sysexData + 8, rawData, size);
    sysexData[8 + size] = calculateChecksum(rawData, size);
    sysexData[8 + size + 1] = 0xF7;

    Midi::SysExMessage msg = Midi::SysExMessage(sysexData, 9 + size);
    midi->send(msg);
}
void Katana::set(uint8_t address[4], uint8_t data)
{
    uint8_t rawData[1] = {data};
    sendCommand(0x12, address, rawData, 1);
}

void Katana::poll() {
    midi->poll();
}
