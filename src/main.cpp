#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "knob.h"
#include "midi.h"
#include <Bounce2.h>

U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI lcd(U8G2_R0, 4, 3, 2);

USB usb;
Midi::Midi katana(&usb);

Bounce sw = Bounce();
void setup()
{
    lcd.begin();
    Serial.begin(115200);
    if (usb.Init() == -1) {
        while (1);
    }
    delay( 200 );

    pinMode(5, INPUT_PULLUP);
    sw.attach(5);
    sw.interval(5);
    Serial.println("Initialized");
}


Knob knob("Time", 500, 0, 2000, 15, 29);
Knob knob2("FB", 20, 0, 100, 64, 29);
Knob knob3("Level", 100, 0, 120, 113, 29);
uint16_t val = 0;



void loop()
{
    sw.update();
    usb.Task();
    if ( usb.getUsbTaskState() == USB_STATE_RUNNING )
    {
        katana.poll();

        if (sw.fell())
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
        strlen = lcd.getStrWidth("On");
        lcd.drawStr(64 - strlen/2, 62, "On");

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
