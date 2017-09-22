#include "katana.h"
#include "../utils.h"

byte Katana::calculateChecksum(byte* vals, byte valsSize)
{
    byte acc = 0;
    for(byte i = 0; i < valsSize; i++)
    {
        acc = (acc + vals[i]) & 0x7F;
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


    Midi::SysExMessage msg = Midi::SysExMessage(sysexData, 10 + size);
    midi->send(msg);
}
void Katana::set(byte address[4], byte data)
{
    byte rawData[1] = {data};
    sendCommand(0x12, address, rawData, 1);
}

void Katana::query(byte address[4], byte size) { //, Callback callback) {
    byte rawData[4] = {0x00, 0x00, 0x00, size};
    //callbacks[0].free = false;
    //memcpy(callbacks[0].addr, address, 4);
    //callbacks[0].callback = callback;
    sendCommand(0x11, address, rawData, 4);
}
void Katana::update() {
    midi->update(); // update MIDI interface and queues

    while(midi->has()) {
        auto msg = midi->receive();
        Serial.print("Received: ");
        Utils::printHex(msg.rawData, msg.size);
        //Serial.println(msg.getType());
        if (msg.rawData[0] == 0xF0) {
            /*for(byte i = 0; i < 1; i++) {
                if (!callbacks[0].free) {
                    bool compare = true;
                    for(byte j = 0; j < 4; j++) {
                        if (callbacks[i].addr[j] != msg.rawData[8 + j]) {
                            compare = false;
                            break;
                        }
                    }
                    if (compare) {
                        byte size = msg.size - 14;
                        byte* data = new byte[size];
                        memcpy(data, (msg.rawData + 12), size);
                        auto callback = callbacks[i].callback;
                        callback.callback(callback.obj, data, size);
                        delete data;
                    }
                }
            }*/
            for(byte i = 0; i < rangeCount; i++) {
                byte* dest = ranges[i].inRange(msg.rawData + 8);
                if (dest != nullptr) {
                    memcpy(dest, msg.rawData + 12, msg.size -14);
                    break;
                }
            }
        }
    }

}

byte* Katana::registerRange(byte baseAddr[4], byte size) {
    ranges[rangeCount] = Range(baseAddr, size);
    return ranges[rangeCount++].data;
}

Range::Range(byte baseAddr[4], byte size) {
    lastAddr[0] = baseAddr[0];
    lastAddr[1] = baseAddr[1];
    int temp = (int)baseAddr[3];
    temp += size;
    lastAddr[2] += (temp/128);
    lastAddr[3] = temp % 128;
    data = new byte[size];
    memset(data, 0x00, size);
    memcpy(this->baseAddr, baseAddr, 4);
    //Utils::printHex(lastAddr, 4);
}

byte* Range::inRange(byte addr[4]) {
    //Utils::printHex(addr, 4);
    //Utils::printHex(baseAddr, 4);
    int as = baseAddr[2] * 128 + baseAddr[3];
    int al = lastAddr[2] * 128 + lastAddr[3];
    int a = addr[2] * 128 + addr[3];

    if ( (a < as) || (a > al)) {
        return nullptr;
    }
    //Serial.print(as); Serial.print(" ");
    //Serial.print(al); Serial.print(" ");
    //Serial.println(a);
    byte offset = a - as;
    //Serial.println(offset);
    return (data + offset);
    //last
}
