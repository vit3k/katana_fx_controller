#ifndef H_PANELS
#define H_PANELS

#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include "../effects/effects.h"
#include "knob.h"
#include <Bounce2.h>
#include "rotaryEncoder.h"
#include "slotListPanel.h"
#include "effectPanel.h"
#include "effectListPanel.h"
#include "panel.h"

class Panels {
private:
    U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI* lcd;//(U8G2_R0, 49, 48, 47);
    Effects* effects;
    EffectPanel* effectPanel;
    EffectListPanel* effectListPanel;
    SlotListPanel* slotListPanel;
    Panel* current;
    Bounce* homeSwitch;
public:
    void setup() {
        lcd = new U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI(U8G2_R0, 15, 20, 16);
        lcd->begin();
    }
    void show(Panel* panel) { current = panel; }
    void draw();
    void update();
    Panels(Effects* effects, EffectPanel* effectPanel, EffectListPanel* effectListPanel, SlotListPanel* slotListPanel, Bounce* homeSwitch):
        effects(effects), effectPanel(effectPanel), effectListPanel(effectListPanel), slotListPanel(slotListPanel), homeSwitch(homeSwitch) {
        effectPanel->setPanels(this);
        effectListPanel->setPanels(this);
        slotListPanel->setPanels(this);
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
    void showSlotList() {
        show(slotListPanel);
    }
};
#endif
