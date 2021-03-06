#include "effectPanel.h"
#include "panels.h"
void EffectPanel::updateKnobs() {
    EffectParam** params = effectSlot->params();
    byte paramsCount = effectSlot->paramsCount();

    byte pageCount = ceil( (float)paramsCount / 3.0f);
    knobCount = 3;
    if (currentPage == (pageCount - 1)) {
        knobCount = paramsCount % 3;
        knobCount = knobCount == 0 ? 3 : knobCount;
    }

    for(byte i = 0; i < knobCount; i++) {
        auto param = params[currentPage * 3 + i];
        auto multiplier = 1;
        if (param->maxValue - param->minValue > 200) {
            multiplier = 16;
        }
        auto delta = rotaryEncoders[i]->delta(multiplier);
        auto value = effectSlot->value(param);
        if (delta != 0) {
            effectSlot->updateParam(param, value + delta);
        }

        knobs[i].setKnob(param->name.c_str(), value, param->minValue, param->maxValue);
    }
}

void EffectPanel::show(EffectSlot *effectSlot) {
    this->effectSlot = effectSlot;
    currentPage = 0;
    currentKnob = 0;
    updateKnobs();
}

byte EffectPanel::calculateKnobCount() {

    return knobCount;
}

void EffectPanel::update() {
    if (pageSwitch->fell()) {
        Serial.println("pageswith fell");
        byte pageCount = ceil( (float)effectSlot->paramsCount() / 3.0f);
        currentPage++;
        if (currentPage >= pageCount) {
            currentPage = 0;
        }
        updateKnobs();
    }

    if (typeSwitch->fell() && effectSlot->effectsCount() > 1 ) {

        panels->showEffectList(effectSlot);
    }

    if (onOffSwitch->fell()) {
        effectSlot->onoff();
    }
    updateKnobs();
}

void EffectPanel::draw(U8G2* lcd) {
    lcd->setFont(u8g2_font_5x7_tf);
    lcd->setFontMode(0);
    lcd->setDrawColor(1);
    int strlen = 0;

    lcd->drawStr(0, 6, effectSlot->name.c_str());
    if (effectSlot->effectsCount() > 1) {
        strlen = lcd->getStrWidth("Type");
        lcd->drawStr(15 - strlen/2, 62, "Type");
    }
    char onOffString[4] = "Off";
    if (effectSlot->enabled)
    {
        strcpy(onOffString, "On");
    }
    strlen = lcd->getStrWidth(onOffString);
    lcd->drawStr(64 - strlen/2, 62, onOffString);

    strlen = lcd->getStrWidth("Page");
    lcd->drawStr(113 - strlen/2, 62, "Page");
    strlen = lcd->getStrWidth(effectSlot->currentName().c_str());
    lcd->drawStr(128 - strlen, 6, effectSlot->currentName().c_str());


    for(byte i = 0; i < knobCount; i++) {
        knobs[i].draw(lcd);
    }
}

