#include "panels.h"
#include <math.h>

void Panels::draw() {
    lcd->firstPage();
    do {
        current->draw(lcd);
    } while ( lcd->nextPage() );
}
void Panels::update() {
    if (homeSwitch->fell()) {
        showSlotList();
    }
    current->update();
}

