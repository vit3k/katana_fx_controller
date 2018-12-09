#include "midi.h"
#include <usbhub.h>
#include <usbh_midi.h>
#include "../utils.h"

namespace Midi {
    void Midi::setup() {
        if (usb.Init() == -1) {
            while (1);
        }
        delay( 200 );
    }

    Message::Message(const Message& a) {
        rawData = new byte[a.size];
        memcpy(rawData, a.rawData, a.size);
        size = a.size;
    }

    Message& Message::operator=(const Message& other) {
        //Serial.println("Message assign");
        rawData = new byte[other.size];
        memcpy(rawData, other.rawData, other.size);
        size = other.size;
        return *this;
    }
    ProgramChangeMessage::ProgramChangeMessage(byte* rawData) {
        this->rawData = rawData;
        program = rawData[1];
    }

    ProgramChangeMessage::ProgramChangeMessage(byte program) {
        this->program = program;
        rawData = new byte[2];
        rawData[0] = 0b11000000;
        rawData[1] = program & 0b01111111;
    }

    SysExMessage::SysExMessage(byte* rawData, byte size) {
        this->rawData = new byte[size];
        memcpy(this->rawData, rawData, size);
        this->size = size;
    }
    Message Message::parse(byte* rawData, byte length) {
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
        byte size = 0;

        byte recvBuf[MIDI_EVENT_PACKET_SIZE];
        byte readPtr = 0;
        byte status = midi->RecvData(&bytesRcvd, recvBuf);

        if (status != 0) return;
        byte* p = recvBuf;
        while (readPtr < MIDI_EVENT_PACKET_SIZE)  {
            if (*p == 0 && *(p + 1) == 0) break; //data end

            MidiSysEx::Status rc = sysEx.set(p);

            switch(rc) {
                case MidiSysEx::nonsysex:
                    p++;
                    size = midi->lookupMsgSize(*p);
                    p += 3;
                    break;
                case MidiSysEx::done:
                    {
                        SysExMessage msg(sysEx.get(), sysEx.getSize());
                        inputQueue.push(msg);
                    }
                case MidiSysEx::overflow:
                    sysEx.clear();
                default:
                    p += 4;
                    break;
            }
            readPtr += 4;
        }
    }

    void Midi::send(Message& msg) {
        //Utils::printHex(msg.rawData, msg.size);
        outputQueue.push(msg);
    }

    void Midi::sendQueue() {
        while(outputQueue.has()) {
            auto msg = outputQueue.pop();
            Serial.print("Sending ");
            Utils::printHex(msg.rawData, msg.size);
            midi->SendData(msg.rawData);
        }

    }
    bool Midi::isRunning() {
        usb.Task();
        return usb.getUsbTaskState() == USB_STATE_RUNNING;
    }

    void Midi::update() {
        if (isRunning()) {
            sendQueue();
            poll(); // populating queue
        }
    }
    bool Midi::has() {
        return inputQueue.has();
    }
    Message Midi::receive() {
        return inputQueue.pop();
    }
    byte USBH_MIDI_ext::Init(byte parent, byte port, bool lowspeed)
    {
        auto rcode = USBH_MIDI::Init(parent, port, lowspeed);
        if (rcode == 0) {
            this->port = port;
        }
        return rcode;
    }

    MidiSysEx::MidiSysEx()
    {
            clear();
    }

    void MidiSysEx::clear()
    {
            pos = 0;
            buf[0] = 0;
    }

    MidiSysEx::Status MidiSysEx::set(uint8_t *p)
    {
            MidiSysEx::Status rc = MidiSysEx::ok;
            uint8_t cin = *(p) & 0x0f;

            //SysEx message?
            if( (cin & 0xc) != 4 ) return MidiSysEx::nonsysex;

            switch(cin) {
                case 4:
                case 7:
                    if( pos+2 < MIDI_EVENT_PACKET_SIZE ) {
                            buf[pos++] = *(p+1);
                            buf[pos++] = *(p+2);
                            buf[pos++] = *(p+3);
                    }else{
                            rc = MidiSysEx::overflow;
                    }
                    break;
                case 5:
                    if( pos+1 < MIDI_EVENT_PACKET_SIZE ) {
                            buf[pos++] = *(p+1);
                            buf[pos++] = *(p+2);
                    }else{
                            rc = MidiSysEx::overflow;
                    }
                    break;
                case 6:
                    if( pos < MIDI_EVENT_PACKET_SIZE ) {
                            buf[pos++] = *(p+1);
                    }else{
                            rc = MidiSysEx::overflow;
                    }
                    break;
                default:
                    break;
            }
            //SysEx end?
            if((cin & 0x3) != 0) {
                    rc = MidiSysEx::done;
            }
            return(rc);
    }
}
