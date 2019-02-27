#include "panels.h"

void EffectListPanel::show(EffectSlot* effectSlot) {
    this->effectSlot = effectSlot;
    current = effectSlot->current;
    names = effectSlot->list();
    init();
}

String* EffectListPanel::list() {
    return names;
}

byte EffectListPanel::listCount() {
    return effectSlot->effectsCount();
}

void EffectListPanel::onSelect() {
    delete[] names;
    panels->showEffect(effectSlot);
}

void EffectListPanel::onChange() {
    effectSlot->change(current);
}