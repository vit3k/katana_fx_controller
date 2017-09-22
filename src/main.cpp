#include <SPI.h>
#include <Wire.h>
#include "gui/panels.h"
#include "katana/midi.h"

#include <Bounce2.h>
#include "katana/katana.h"
#include "effects/effects.h"
#include "utils.h"

Midi::Midi midi;
Katana katana(&midi);

Bounce sw1 = Bounce();
Bounce sw2 = Bounce();
Bounce sw3 = Bounce();
Bounce sw4 = Bounce();

Effects effects(&katana);
EffectPanel effectPanel(&sw4, &sw2);
EffectListPanel effectListPanel(&sw2, &sw3, &sw1);
Panels panels(&effects, &effectPanel, &effectListPanel);

void setup()
{
    panels.setup();

    Serial.begin(115200);
    midi.setup();

    pinMode(22, INPUT_PULLUP);
    sw1.attach(22);
    sw1.interval(5);

    pinMode(23, INPUT_PULLUP);
    sw2.attach(23);
    sw2.interval(5);

    pinMode(24, INPUT_PULLUP);
    sw3.attach(24);
    sw3.interval(5);

    pinMode(25, INPUT_PULLUP);
    sw4.attach(25);
    sw4.interval(5);

    panels.showEffect();

    Serial.println(F("Initialized"));
}

void loop()
{
    sw1.update();
    sw2.update();
    sw3.update();
    sw4.update();

    //katana.update();

    panels.update();
    panels.draw();
    /*if (sw1.fell()) {
        byte addr[4] = {0x60, 0x00, 0x00, 0x30};
        katana.query(addr, 9, Callback(nullptr, [](void* obj, byte* data, byte size) {
            Utils::printHex(data, size);
        }));
    }*/
}
