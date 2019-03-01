#include "slotListPanel.h"
#include "panels.h"

String* SlotListPanel::list() {
    return names;
}
byte SlotListPanel::listCount() {
    return slotsCount;
}
void SlotListPanel::onSelect() {
    panels->showEffect(slots[current]);
}
void SlotListPanel::update() {
    ListPanel::update();
    if (onoffSwitch->fell()) {
        slots[current]->onoff();
    }
}