#ifndef H_MIDI
#define H_MIDI

#include <usbh_midi.h>
#include <usbhub.h>
#include "../queue.h"

namespace Midi {

    enum MessageType {
        Generic, ProgramChange, SysEx
    };
    class Message {
    public:
        byte size = 0;
        byte* rawData;
        Message(byte* _rawData): rawData(_rawData) {};
        Message() {};
        ~Message() {
            delete[] rawData;
        };
        Message(const Message& a);
        Message& operator=(const Message& other);
        static Message parse(byte* rawData, byte length);
        virtual MessageType getType() { return Generic; };
    };

    class ProgramChangeMessage : public Message {
    public:
        byte program = 0;
        ProgramChangeMessage(byte* rawData);
        ProgramChangeMessage(byte program);
        virtual MessageType getType() { return ProgramChange; };
    };

    class SysExMessage : public Message {
    public:
        SysExMessage(byte* rawData, byte size);
        virtual MessageType getType() { return SysEx; };
    };

    class USBH_MIDI_ext : public USBH_MIDI {
    public:
        byte port;
        byte Init(byte parent, byte port, bool lowspeed);
        USBH_MIDI_ext(USB* usb): USBH_MIDI(usb) {};
        virtual ~USBH_MIDI_ext() {}
    };

    class MidiSysEx {
    private:
            uint8_t pos;
            uint8_t buf[MIDI_EVENT_PACKET_SIZE];
    public:
            typedef enum {
                    nonsysex = 0,
                    ok       = 1,
                    done     = 0xfe,
                    overflow = 0xff
            } Status;

            MidiSysEx();
            void clear();
            MidiSysEx::Status set(uint8_t *p);
            inline uint8_t *get(){return buf;};
            inline uint8_t getSize(){return pos;};
    };

    class Midi {
        USBH_MIDI_ext* midi;
        USB usb;
        MidiSysEx sysEx;
        Queue<Message> inputQueue;
        Queue<Message> outputQueue;
        void sendQueue();
    public:
        Midi(): midi(new USBH_MIDI_ext(&usb)) {};
        ~Midi() { delete midi; }
        void setup();
        Message parse(byte* rawData, byte length);
        void poll();
        void send(Message& msg);
        byte getPort() { return midi->port; }
        bool isRunning();
        void update();
        bool has();
        Message receive();
    };
}

#endif
