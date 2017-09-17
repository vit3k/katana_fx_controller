#include "panels.h"

void EffectPanel::updateKnobs() {
    //knobCount = calculateKnobCount();
    EffectParam* params;
    uint8_t paramsCount;
    effectSlot->params(params, paramsCount);
    Serial.println(params[0].name);
    uint8_t pageCount = ceil( (float)paramsCount / 3.0f);
    knobCount = 3;
    if (currentPage == (pageCount - 1)) {
        knobCount = paramsCount % 3;
        knobCount = knobCount == 0 ? 3 : knobCount;
    }

    for(uint8_t i = 0; i < knobCount; i++) {
        EffectParam param = params[currentPage * 3 + i];
        knobs[i].setKnob(param.name, param.value, param.minValue, param.maxValue);

    }
    //delete params;
}

void EffectPanel::show(EffectSlot *effectSlot) {
    this->effectSlot = effectSlot;
    currentPage = 0;
    currentKnob = 0;
    updateKnobs();
}

uint8_t EffectPanel::calculateKnobCount() {

    return knobCount;
}

void EffectPanel::update() {
    if (pageSwitch->fell()) {
        uint8_t pageCount = ceil( (float)effectSlot->paramsCount() / 3.0f);
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
    strlen = lcd.getStrWidth(effectSlot->currentName().c_str());
    lcd.drawStr(128 - strlen, 6, effectSlot->currentName().c_str());


    for(uint8_t i = 0; i < knobCount; i++) {
        knobs[i].draw(lcd);
    }
}

void EffectListPanel::show(EffectSlot* effectSlot) {
    this->effectSlot = effectSlot;
    firstVisible = effectSlot->current;
    if (firstVisible + 6 > effectSlot->effectsCount()) {
        firstVisible = effectSlot->effectsCount() - 6;
    }
    current = effectSlot->current;
}
void EffectListPanel::draw(U8G2& lcd) {
    lcd.setFont(u8g2_font_5x7_tf);
    String* names;
    uint8_t namesCount;
    effectSlot->list(names, namesCount);

    uint8_t last = min(firstVisible + 5, namesCount - 1);
    for(uint8_t i = 0; i < last; i++) {
        if ((firstVisible + i) != effectSlot->current) {
            lcd.setDrawColor(1);
        }
        else {
            lcd.setDrawColor(1);
            lcd.drawBox(0, i * 10 - 1, 120, 8);
            lcd.setDrawColor(0);
        }

        lcd.drawStr(0, i * 10 + 6, names[firstVisible + i].c_str());
    }

    delete names;
}

void EffectListPanel::update() {
    if (exitSwitch->fell()) {
        panels->showEffect(effectSlot);
    }
    // TODO: fix navigation
    if (nextSwitch->fell()) {
        current++;
        if (current >= effectSlot->effectsCount()) {
            current = 0;
        }
        effectSlot->change(current);
        if (current - firstVisible >= 6) {
            firstVisible++;
        }
        if (firstVisible + 6 > effectSlot->effectsCount()) {
            firstVisible = effectSlot->effectsCount() - 6;
        }
    }

    if (prevSwitch->fell()) {
        current--;
        if (current < 0) {
            current = effectSlot->effectsCount() - 1;
        }
        effectSlot->change(current);
        if (current < firstVisible) {
            firstVisible = current;
        }
    }
}
