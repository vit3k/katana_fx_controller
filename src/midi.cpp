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
        Serial.println("received");
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


    //  function to get single string description
    uint8_t Midi::getstrdescr( uint8_t idx, char* string)
    {
        uint8_t addr = getAddress();
      uint8_t buf[ 256 ];
      uint8_t rcode;
      uint8_t length;
      uint8_t i;
      uint16_t langid;
      rcode = usb->getStrDescr( addr, 0, 1, 0, 0, buf );  //get language table length
      if ( rcode ) {
        return rcode;
      }
      length = buf[0];      //length is the first byte
      rcode = usb->getStrDescr( addr, 0, length, 0, 0, buf );  //get language table
      if ( rcode ) {
        return rcode;
      }
      langid = (buf[3] << 8) | buf[2];
      rcode = usb->getStrDescr( addr, 0, 1, idx, langid, buf );
      if ( rcode ) {
        return rcode ;
      }
      length = buf[ 0 ];
      rcode = usb->getStrDescr( addr, 0, length, idx, langid, buf );
      if ( rcode ) {
        return rcode;
      }
      string = new char[length/2 - 2];
      for ( i = 2; i < length; i += 2 ) {   //string is UTF-16LE encoded
        string[i/2 - 2] = (char) buf[i];
      }
      string[i/2 - 2] = (char)0;
      return ( rcode );
    }

    char* Midi::getDeviceName() {
        if (this->name == nullptr) {
            uint8_t addr = getAddress();
            USB_DEVICE_DESCRIPTOR buf;
            uint8_t rcode;
            rcode = usb->getDevDescr(addr, 0, DEV_DESCR_LEN, ( uint8_t *)&buf);
            /*if ( rcode ) {
              return rcode;
          }*/
            char* manufacturer;
            char* product;

            if ( buf.iManufacturer > 0 ) {
                getstrdescr( buf.iManufacturer, manufacturer );   // get manufacturer string
            }
            if ( buf.iProduct > 0 ) {
                getstrdescr( buf.iProduct, product );   // get manufacturer string
            }
            this->name = "test";
        }
        return this->name;
    }
}
