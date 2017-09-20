#include "midi.h"
#include <usbhub.h>
#include <usbh_midi.h>
#include "utils.h"

namespace Midi {
    void Midi::setup() {
        if (usb.Init() == -1) {
            while (1);
        }
        delay( 200 );
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
        //this->rawData = rawData;
        this->rawData = new byte[size];
        memcpy(this->rawData, rawData, size);
        this->size = size;
        Utils::printHex(rawData, size);
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

            byte outbuf[3];
            byte rc = midi->extractSysExData(p, outbuf);
            if ( rc == 0 ) {
                p++;
                size = midi->lookupMsgSize(*p);
                // TODO: add received message to queue. It will be read by read method.
                Utils::printHex(p, size);
                SysExMessage msg(p, size);
                inputQueue.push(msg);
                p += 3;
            }
            else {
              p += 4;
            }
            readPtr += 4;
        }
    }

    void Midi::send(Message& msg) {
        outputQueue.push(msg);
    }

    void Midi::sendQueue() {
        Serial.println("Sending queue");
        while(outputQueue.has()) {
            auto msg = outputQueue.pop();
            midi->SendData(msg.rawData);
            Utils::printHex(msg.rawData, msg.size);
        }
    }
    bool Midi::isRunning() {
        usb.Task();
        return usb.getUsbTaskState() == USB_STATE_RUNNING;
    }

    void Midi::update() {
        if (isRunning()) {
            Serial.println("running");
            // TODO: sending from queue
            sendQueue();
            poll(); // populating queue
        }
    }

    byte USBH_MIDI_ext::Init(byte parent, byte port, bool lowspeed)
    {
        auto rcode = USBH_MIDI::Init(parent, port, lowspeed);
        if (rcode == 0) {
            this->port = port;
        }
        return rcode;
    }
}
