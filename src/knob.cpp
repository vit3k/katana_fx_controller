#include "knob.h"

void Knob::draw(U8G2 &lcd)
{
    float angle = (float)((val - minVal))/(float)((abs(minVal) + abs(maxVal))) * 1.5 * PI + 0.25 * PI;
    uint8_t endpointX = x - 8 * sin(angle);
    uint8_t endpointY = y + 8 * cos(angle);

    lcd.setDrawColor(1);
    lcd.drawDisc(x, y, 8);
    lcd.setDrawColor(0);
    lcd.drawLine(x, y, endpointX, endpointY);
    lcd.setFont(u8g2_font_5x7_tf);
    lcd.setFontMode(0);
    lcd.setDrawColor(1);
    char buffer[10];
    dtostrf(val, 0, 0, buffer);
    int strlen = lcd.getStrWidth(buffer);
    lcd.drawStr(x - strlen/2, y + 16, buffer);
    char* titleBuffer = title.c_str();
    strlen = lcd.getStrWidth(titleBuffer);
    lcd.drawStr(x - strlen/2, y - 10, titleBuffer);
    //Serial.println(title);
}
