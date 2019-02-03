
#ifndef Knob_H
#define Knob_H

#include <Arduino.h>
#include <U8g2lib.h>
#include <String.h>

class Knob
{
private:
    String title;
    int16_t val, minVal, maxVal;
    byte x, y;
    int32_t lastRead;
public:
    void draw(U8G2* lcd);
    void setVal(int16_t val) { this->val = val; };
    void setKnob(String title, int16_t val, int16_t minVal, int16_t maxVal) {
        this->title = title;
        this->val = val;
        this->minVal = minVal;
        this->maxVal = maxVal;
    }
    void placeKnob(byte x, byte y) {
        this->x = x;
        this->y = y;
    }
    Knob(String title, int16_t val, int16_t minVal, int16_t maxVal, byte x, byte y):
        title(title), val(val), minVal(minVal), maxVal(maxVal), x(x), y(y) {};
    Knob(byte x, byte y) : x(x), y(y) {}
};

#endif
