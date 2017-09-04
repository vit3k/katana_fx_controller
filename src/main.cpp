#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "knob.h"
#include "midi.h"
#include <Bounce2.h>

U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI lcd(U8G2_R0, 4, 3, 2);

USB usb;
Midi::Midi katana(&usb);

Bounce sw1 = Bounce();
Bounce sw2 = Bounce();
Bounce sw3 = Bounce();
void setup()
{
    lcd.begin();
    Serial.begin(115200);
    if (usb.Init() == -1) {
        while (1);
    }
    delay( 200 );

    pinMode(5, INPUT_PULLUP);
    sw1.attach(5);
    sw1.interval(5);

    pinMode(6, INPUT_PULLUP);
    sw2.attach(6);
    sw2.interval(6);

    pinMode(7, INPUT_PULLUP);
    sw3.attach(7);
    sw3.interval(7);
    Serial.println("Initialized");
}


Knob knob("Time", 500, 0, 2000, 15, 29);
Knob knob2("FB", 20, 0, 100, 64, 29);
Knob knob3("Level", 100, 0, 120, 113, 29);
uint16_t val = 0;

bool delayOn = true;

uint8_t calculateChecksum(uint8_t* vals, uint8_t valsSize)
{
    uint8_t acc = 0;
    for(uint8_t i = 0; i < valsSize; i++)
    {
        acc += vals[i] & 0x7F;
    }

    return (128 - acc) & 0x7F;
}
void sendCommand(uint8_t command, uint8_t address[4], uint8_t data[4], uint8_t dataSize)
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
    katana.send(msg);
}
void set(uint8_t address[4], uint8_t data)
{
    uint8_t rawData[1] = {data};
    sendCommand(0x12, address, rawData, 1);
}

void loop()
{
    sw1.update();
    sw2.update();
    sw3.update();
    usb.Task();
    if ( usb.getUsbTaskState() == USB_STATE_RUNNING )
    {
        katana.poll();

        if (sw1.fell())
        {
            Serial.println("Sending sysex");
            //static uint8_t data[15] = {0xF0, 0x41, 0x00, 0x00, 0x00, 0x00, 0x33, 0x12, 0x00, 0x00, 0x04, 0x20, 0x03, 0x59, 0xF7};
            //static Midi::SysExMessage msg = Midi::SysExMessage(data, 15);

            //static uint8_t data[18] = {0xF0, 0x41, 0x00, 0x00, 0x00, 0x00, 0x33, 0x11, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x01, 0x5B, 0xF7};
            //static Midi::SysExMessage msg = Midi::SysExMessage(data, 18);

            static uint8_t data[15] = {0xF0, 0x41, 0x00, 0x00, 0x00, 0x00, 0x33, 0x12, 0x7f, 0x00, 0x00, 0x01, 0x01, 0x7F, 0xF7};
            static Midi::SysExMessage msg = Midi::SysExMessage(data, 15);
            //Midi::ProgramChangeMessage msg(2);
            katana.send(msg);
            Serial.println("Sysex sent");

        }

        if (sw2.fell())
        {
            delayOn = !delayOn;
            uint8_t delayBaseAddr[4] = {0x60, 0x00, 0x05, 0x60};
            //static uint8_t data[15] = {0xF0, 0x41, 0x00, 0x00, 0x00, 0x00, 0x33, 0x12, 0x60, 0x00, 0x05, 0x60, delayOn, 0x7F, 0xF7};
            set(delayBaseAddr, delayOn );
        }
    }

    val++;
    if( val > 2000)
        val = 0;
    knob.setVal(val);
    lcd.firstPage();
    do {
        lcd.setFont(u8g2_font_5x7_tf);
        lcd.setFontMode(0);
        lcd.setDrawColor(1);
        lcd.drawStr(0, 6, "Delay *");
        int strlen = lcd.getStrWidth("Type");
        lcd.drawStr(15 - strlen/2, 62, "Type");
        char onOffString[4] = "Off";
        if (delayOn)
        {
            strcpy(onOffString, "On");
        }
        strlen = lcd.getStrWidth(onOffString);
        lcd.drawStr(64 - strlen/2, 62, onOffString);

        strlen = lcd.getStrWidth("Page");
        lcd.drawStr(113 - strlen/2, 62, "Page");
        strlen = lcd.getStrWidth("Analog");
        lcd.drawStr(128 - strlen, 6, "Analog");
        knob.draw(lcd);
        knob2.draw(lcd);
        knob3.draw(lcd);

    } while ( lcd.nextPage() );

    //delay(100);
}
