
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
    uint8_t x, y;
public:
    void draw(U8G2 &lcd);
    void setVal(int8_t val) { this->val = val; };
    Knob(String title, int16_t val, int16_t minVal, int16_t maxVal, uint8_t x, uint8_t y):
        title(title), val(val), minVal(minVal), maxVal(maxVal), x(x), y(y) {};
};

#endif
