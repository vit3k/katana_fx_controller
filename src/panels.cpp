#include "panels.h"

void EffectPanel::updateKnobs() {
    knobCount = calculateKnobCount();
    for(uint8_t i = 0; i < knobCount; i++) {
        EffectParam param = effectSlot->currentEffect()->params[currentPage * 3 + i];
        knobs[i].setKnob(param.name, param.value, param.minValue, param.maxValue);
    }
}
void EffectPanel::show(EffectSlot *effectSlot) {
    this->effectSlot = effectSlot;
    currentPage = 0;
    currentKnob = 0;
    updateKnobs();
}

uint8_t EffectPanel::calculateKnobCount() {
    uint8_t pageCount = ceil( (float)effectSlot->currentEffect()->paramsCount / 3.0f);
    uint8_t knobCount = 3;
    if (currentPage == (pageCount - 1)) {
        knobCount = effectSlot->currentEffect()->paramsCount % 3;
        knobCount = knobCount == 0 ? 3 : knobCount;
    }
    return knobCount;
}

void EffectPanel::update() {
    if (pageSwitch->fell()) {
        uint8_t pageCount = ceil( (float)effectSlot->currentEffect()->paramsCount / 3.0f);
        currentPage++;
        if (currentPage >= pageCount) {
            currentPage = 0;
        }
        updateKnobs();
    }

    if (typeSwitch->fell()) {

        panels->showEffectList(effectSlot);
    }
}

void EffectPanel::draw(U8G2& lcd) {
    lcd.setFont(u8g2_font_5x7_tf);
    lcd.setFontMode(0);
    lcd.setDrawColor(1);
    lcd.drawStr(0, 6, effectSlot->name.c_str());
    int strlen = lcd.getStrWidth("Type");
    lcd.drawStr(15 - strlen/2, 62, "Type");
    char onOffString[4] = "Off";
    if (effectSlot->enabled)
    {
        strcpy(onOffString, "On");
    }
    strlen = lcd.getStrWidth(onOffString);
    lcd.drawStr(64 - strlen/2, 62, onOffString);

    strlen = lcd.getStrWidth("Page");
    lcd.drawStr(113 - strlen/2, 62, "Page");
    strlen = lcd.getStrWidth(effectSlot->currentEffect()->name.c_str());
    lcd.drawStr(128 - strlen, 6, effectSlot->currentEffect()->name.c_str());


    for(uint8_t i = 0; i < knobCount; i++) {
        knobs[i].draw(lcd);
    }
}

void EffectListPanel::show(EffectSlot* effectSlot) {
    this->effectSlot = effectSlot;
    firstVisible = effectSlot->currentEffectIdx;
    if (firstVisible + 6 > effectSlot->effectsCount) {
        firstVisible = effectSlot->effectsCount - 6;
    }
    current = effectSlot->currentEffectIdx;
}
void EffectListPanel::draw(U8G2& lcd) {
    lcd.setFont(u8g2_font_5x7_tf);
    uint8_t last = min(firstVisible + 5, effectSlot->effectsCount - 1);
    for(uint8_t i = 0; i < last; i++) {
        if ((firstVisible + i) != effectSlot->currentEffectIdx) {
            lcd.setDrawColor(1);
        }
        else {
            lcd.setDrawColor(1);
            lcd.drawBox(0, i * 10 - 1, 120, 8);
            lcd.setDrawColor(0);
        }

        lcd.drawStr(0, i * 10 + 6, effectSlot->effects[firstVisible + i].name.c_str());
    }
}

void EffectListPanel::update() {
    if (exitSwitch->fell()) {
        panels->showEffect(effectSlot);
    }
    // TODO: fix navigation
    if (nextSwitch->fell()) {
        current++;
        if (current >= effectSlot->effectsCount) {
            current = 0;
        }
        effectSlot->changeEffect(current);
        if (current - firstVisible >= 6) {
            firstVisible++;
        }
        if (firstVisible + 6 > effectSlot->effectsCount) {
            firstVisible = effectSlot->effectsCount - 6;
        }
    }

    if (prevSwitch->fell()) {
        current--;
        if (current < 0) {
            current = effectSlot->effectsCount - 1;
        }
        effectSlot->changeEffect(current);
        if (current < firstVisible) {
            firstVisible = current;
        }
    }
}
