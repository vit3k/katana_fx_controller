#include <usbh_midi.h>
#include <usbhub.h>

namespace Midi {

    enum MessageType {
        Generic, ProgramChange, SysEx
    };
    class Message {
    public:
        uint8_t size = 0;
        uint8_t* rawData;
        Message(uint8_t* _rawData): rawData(_rawData) {};
        Message() {};
        ~Message() { delete rawData; };
        static Message parse(uint8_t* rawData, uint8_t length);
        virtual MessageType getType() { return Generic; };
    };

    class ProgramChangeMessage : public Message {
    public:
        uint8_t program = 0;
        ProgramChangeMessage(uint8_t* rawData);
        ProgramChangeMessage(uint8_t program);
        virtual MessageType getType() { return ProgramChange; };
    };

    class SysExMessage : public Message {
    public:
        SysExMessage(uint8_t* rawData, uint8_t size);
        virtual MessageType getType() { return SysEx; };
    };

    class USBH_MIDI_ext : public USBH_MIDI {
    public:
        uint8_t port;
        uint8_t Init(uint8_t parent, uint8_t port, bool lowspeed);
        USBH_MIDI_ext(USB* usb): USBH_MIDI(usb) {};
    };

    class Midi {
        USBH_MIDI_ext* midi;
        USB* usb;
        char* name;

    public:
        Midi(USB* usb): midi(new USBH_MIDI_ext(usb)), usb(usb) {};
        ~Midi() { delete midi; }
        void setup();
        Message parse(uint8_t* rawData, uint8_t length);
        void poll();
        void send(Message& msg);
        uint8_t getAddress();
        uint8_t getPort() { return midi->port; }
    };
}
