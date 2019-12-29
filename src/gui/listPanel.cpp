#include "listPanel.h"
#include <math.h>

void ListPanel::init() {
    if (current < 6) {
        firstVisible = 0;
    } else if (current > (listCount() - 6)) {
        firstVisible = listCount() - 6;
    } else {
        firstVisible = current;
    }
}
void ListPanel::draw(U8G2* lcd) {
    lcd->setFont(u8g2_font_5x7_tf);
    String* names = list();
    byte namesCount = listCount();
    byte first = firstVisible + 6;
    byte last = min(first, namesCount);
    for(byte i = firstVisible; i < last; i++) {
        if (i != current) {
            lcd->setDrawColor(1);
        }
        else {
            lcd->setDrawColor(1);
            lcd->drawBox(0, (i - firstVisible) * 10 - 1, 120, 8);
            lcd->setDrawColor(0);
        }

        lcd->drawStr(0, (i - firstVisible) * 10 + 6, names[i].c_str());
    }
}

void ListPanel::update() {
    if (select->fell()) {
        onSelect();
    }
    byte count = listCount();

    auto delta = change->delta();
    if (delta > 0) {
        current++;
        if (current >= count) {
            current = 0;
            firstVisible = 0;
        }
        onChange();
        if ((current - firstVisible) >= 6) {
            firstVisible++;
        }
    }
    if (delta< 0) {
        if (current == 0) {
            current = count;
            firstVisible = max(count - 6, 0);
        }
        current--;

        onChange();
        if (current < firstVisible) {
            firstVisible = current;
        }
    }
}