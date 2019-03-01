#include <SPI.h>
#include <Wire.h>
#include "gui/panels.h"
#include "katana/midi.h"

#include <Bounce2.h>
#include "katana/katana.h"
#include "effects/effects.h"
#include "utils.h"
#include <gui/rotaryEncoder.h>

Midi::Midi midi;
Katana katana(&midi);

Bounce sw1 = Bounce();
Bounce sw2 = Bounce();
Bounce sw3 = Bounce();
Bounce homeSwitch = Bounce();
//Bounce sw4 = Bounce();
RotaryEncoder enc1 = RotaryEncoder(1, 2);
RotaryEncoder enc2 = RotaryEncoder(17, 18);
RotaryEncoder enc3 = RotaryEncoder(4, 5);

Effects effects(&katana);
EffectPanel effectPanel(&sw3, &sw1, &sw2, &enc1, &enc2, &enc3);
EffectListPanel effectListPanel(&sw1, &enc1);
SlotListPanel slotListPanel(&sw1, &enc1, (EffectSlot**)effects.slots, SLOTS_COUNT, &sw2);

Panels panels(&effects, &effectPanel, &effectListPanel, &slotListPanel, &homeSwitch);
void update() {
    //enc1.update();
}
IntervalTimer timer;
void setup()
{
    panels.setup();

    Serial.begin(115200);
    //midi.setup();

    pinMode(23, INPUT_PULLUP);
    homeSwitch.attach(23);
    homeSwitch.interval(5);

    pinMode(0, INPUT_PULLUP);
    sw1.attach(0);
    sw1.interval(5);

    pinMode(19, INPUT_PULLUP);
    sw2.attach(19);
    sw2.interval(5);

    pinMode(3, INPUT_PULLUP);
    sw3.attach(3);
    sw3.interval(5);

    panels.showSlotList();

    Serial.println(F("Initialized. Waiting..."));
    //delay(5000);
    //timer.begin(update, 100);
    //katana.init();
    Serial.println(F("Katana connected"));
}

//void printf()
void loop()
{
    homeSwitch.update();
    sw1.update();
    sw2.update();
    sw3.update();
    enc1.update();
    enc2.update();
    enc3.update();

    //attachInterrupt(5, update, FALLING);
    //enc1.delta();
    //katana.update();
    effects.update();
    panels.update();

    panels.draw();
}
