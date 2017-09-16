#ifndef H_PANELS
#define H_PANELS

#include <Arduino.h>
#include "effects.h"

#include <U8g2lib.h>
#include "knob.h"
#include <Bounce2.h>

class Panels;

class Panel {
protected:
    Panels* panels;
public:
    virtual void draw(U8G2& lcd);
    virtual void update();
    void setPanels(Panels* panels) {
        this->panels = panels;
    }
};

class EffectPanel : public Panel {
private:
    uint8_t calculateKnobCount();
    uint8_t knobCount;
    void updateKnobs();
    Bounce* pageSwitch;
    Bounce* typeSwitch;

public:
    EffectPanel(Bounce* pageSwitch, Bounce* typeSwitch): pageSwitch(pageSwitch), typeSwitch(typeSwitch) {}
    uint8_t currentPage = 0;
    uint8_t currentKnob = 0;
    EffectSlot* effectSlot;
    Knob knobs[3] = {
        Knob(15, 29),
        Knob(64, 29),
        Knob(113, 29)
    };
    void update();
    void draw(U8G2& lcd);
    void show(EffectSlot* effectSlot);
};

class EffectListPanel : public Panel {
private:
    EffectSlot* effectSlot;
    uint8_t current = 0;
    uint8_t firstVisible = 0;
    Bounce* exitSwitch;
    Bounce* nextSwitch;
    Bounce* prevSwitch;
public:
    EffectListPanel(Bounce* exitSwitch, Bounce* nextSwitch, Bounce* prevSwitch ): exitSwitch(exitSwitch), nextSwitch(nextSwitch), prevSwitch(prevSwitch) {}
    void show(EffectSlot* effectSlot);
    void draw(U8G2& lcd);
    void update();
};

class Panels {
private:
    Panel* current;
    EffectPanel* effectPanel;
    EffectListPanel* effectListPanel;

public:
    void show(Panel* panel) { current = panel; }
    void draw(U8G2& lcd) { current->draw(lcd); }
    void update() { current->update(); }
    Panels(EffectPanel* effectPanel, EffectListPanel* effectListPanel): effectPanel(effectPanel), effectListPanel(effectListPanel) {
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
};
#endif
