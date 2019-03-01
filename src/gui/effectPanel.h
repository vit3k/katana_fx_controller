#ifndef H_EFFECTPANEL
#define H_EFFECTPANEL

#include "panel.h"
#include <Bounce2.h>
#include "rotaryEncoder.h"
#include "knob.h"
#include "effects/effectSlot.h"

class EffectPanel : public Panel {
private:
    byte calculateKnobCount();
    byte knobCount;
    void updateKnobs();
    Bounce* pageSwitch;
    Bounce* typeSwitch;
    Bounce* onOffSwitch;
    RotaryEncoder* rotaryEncoders[3];
public:
    EffectPanel(Bounce* pageSwitch, Bounce* typeSwitch, Bounce* onOffSwitch, RotaryEncoder* param1, RotaryEncoder* param2, RotaryEncoder* param3):
        pageSwitch(pageSwitch), typeSwitch(typeSwitch), onOffSwitch(onOffSwitch) {
            rotaryEncoders[0] = param1;
            rotaryEncoders[1] = param2;
            rotaryEncoders[2] = param3;
        }
    byte currentPage = 0;
    byte currentKnob = 0;
    EffectSlot* effectSlot;
    Knob knobs[3] = {
        Knob(15, 29),
        Knob(64, 29),
        Knob(113, 29)
    };
    void update();
    void draw(U8G2* lcd);
    void show(EffectSlot* effectSlot);
};

#endif