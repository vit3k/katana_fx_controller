#include "midi.h"
#include <usbhub.h>
#include <usbh_midi.h>
#include "utils.h"

namespace Midi {
    void Midi::setup() {

    }

    ProgramChangeMessage::ProgramChangeMessage(uint8_t* rawData) {
        this->rawData = rawData;
        program = rawData[1];
    }

    ProgramChangeMessage::ProgramChangeMessage(uint8_t program) {
        this->program = program;
        rawData = new uint8_t[2];
        rawData[0] = 0b11000000;
        rawData[1] = program & 0b01111111;
    }

    SysExMessage::SysExMessage(uint8_t* rawData, uint8_t size) {

            this->rawData = rawData;
            this->size = size;
            Utils::printHex(rawData, size);

    }
    Message Message::parse(uint8_t* rawData, uint8_t length) {
        switch( (rawData[0] & 0xF0) >> 4) {
            case 0b1100:
            return ProgramChangeMessage(rawData);
        }
        if (rawData[0] == 0xF0) {
            return SysExMessage(rawData, length);
        }
        return nullptr;
    }

    void Midi::poll() {
        uint16_t bytesRcvd = 0;
        uint8_t size = 0;

        uint8_t recvBuf[MIDI_EVENT_PACKET_SIZE];
        uint8_t readPtr = 0;
        uint8_t status = midi->RecvData(&bytesRcvd, recvBuf);

        if (status != 0) return;
        uint8_t* p = recvBuf;
        while (readPtr < MIDI_EVENT_PACKET_SIZE)  {
            if (*p == 0 && *(p + 1) == 0) break; //data end

            MidiSysEx::Status rc = sysExData.set(p);
            switch (rc) {
                case MidiSysEx::nonsysex :  //No SysEx message send data to Serial MIDI
                    p++;
                    size = midi->lookupMsgSize(*p);
                    Utils::printHex(p, size);
                    p += 3;
                    break;
                case MidiSysEx::done :      //SysEx end. send data to Serial MIDI
                    Utils::printHex(sysExData.get(), sysExData.getSize());
                    /* FALLTHROUGH */
                case MidiSysEx::overflow :  //SysEx buffer over. ignore and flush buffer.
                    sysExData.clear();
                    /* FALLTHROUGH */
                default:
                    p += 4;
                    break;
            }
            readPtr += 4;
        }

    }

    void Midi::send(Message& msg) {
        //if (msg.getType() == SysEx) {

        //    midi->SendSysEx(msg.rawData, msg.size);

        //}
        //else {
            midi->SendData(msg.rawData);
            Utils::printHex(msg.rawData, msg.size);
        //}

    }

    uint8_t Midi::getAddress() {
        midi->GetAddress();
    }

    uint8_t USBH_MIDI_ext::Init(uint8_t parent, uint8_t port, bool lowspeed)
    {
        auto rcode = USBH_MIDI::Init(parent, port, lowspeed);
        if (rcode == 0) {
            this->port = port;
        }
        return rcode;
    }
}
