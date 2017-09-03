#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "knob.h"

U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI lcd(U8G2_R0, 4, 3, 2);

void setup()
{
    lcd.begin();
    Serial.begin(9600);
}

Knob knob("Time", 500, 0, 2000, 15, 29);
Knob knob2("FB", 20, 0, 100, 64, 29);
Knob knob3("Level", 100, 0, 120, 113, 29);
void loop()
{
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
