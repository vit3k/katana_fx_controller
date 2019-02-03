#ifndef H_PANELS
#define H_PANELS

#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include "../effects/effects.h"
#include "knob.h"
#include <Bounce2.h>
#include "rotaryEncoder.h"

class Panels;

class Panel {
protected:
    Panels* panels;
public:
    virtual void draw(U8G2* lcd);
    virtual void update();
    void setPanels(Panels* panels) {
        this->panels = panels;
    }
};

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

class EffectListPanel : public Panel {
private:
    EffectSlot* effectSlot;
    byte current = 0;
    byte firstVisible = 0;
    Bounce* exitSwitch;
    RotaryEncoder* select;
public:
    EffectListPanel(Bounce* exitSwitch, RotaryEncoder* select ):
        exitSwitch(exitSwitch), select(select) {}
    void show(EffectSlot* effectSlot);
    void draw(U8G2* lcd);
    void update();
};

class Panels {
private:
    U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI* lcd;//(U8G2_R0, 49, 48, 47);
    Effects* effects;
    EffectPanel* effectPanel;
    EffectListPanel* effectListPanel;
    Panel* current;
public:
    void setup() {
        lcd = new U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI(U8G2_R0, 49, 48, 47);
        lcd->begin();
    }
    void show(Panel* panel) { current = panel; }
    void draw();
    void update() { current->update(); }
    Panels(Effects* effects, EffectPanel* effectPanel, EffectListPanel* effectListPanel): effects(effects), effectPanel(effectPanel), effectListPanel(effectListPanel) {
        effectPanel->setPanels(this);
        effectListPanel->setPanels(this);
    }
    void showEffectList(EffectSlot* effectSlot) {
        show(effectListPanel);
        effectListPanel->show(effectSlot);
    }
    void showEffect(EffectSlot* effectSlot) {
        show(effectPanel);
        effectPanel->show(effectSlot);
    }
    void showEffect() {
        showEffect(effects->slots[0]);
    }
};
#endif
