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
RotaryEncoder enc1 = RotaryEncoder(5, 6);
RotaryEncoder enc2 = RotaryEncoder(18, 19);
RotaryEncoder enc3 = RotaryEncoder(20, 21);

Effects effects(&katana);
EffectPanel effectPanel(&sw3, &sw1, &sw2, &enc1, &enc2, &enc3);
EffectListPanel effectListPanel(&sw1, &enc1);
SlotListPanel slotListPanel(&sw1, &enc1, (EffectSlot**)effects.slots, 3);

Panels panels(&effects, &effectPanel, &effectListPanel, &slotListPanel, &homeSwitch);
void update() {
    //enc1.update();
}
IntervalTimer timer;
void setup()
{
    panels.setup();

    Serial.begin(115200);
    /*midi.setup();
*/
    pinMode(7, INPUT_PULLUP);
    homeSwitch.attach(7);
    homeSwitch.interval(5);

    pinMode(4, INPUT_PULLUP);
    sw1.attach(4);
    sw1.interval(5);

    panels.showEffect();

    Serial.println(F("Initialized"));
  //  delay(2000);
    //timer.begin(update, 100);

    //katana.init();
}

//void printf()
void loop()
{
    homeSwitch.update();
    sw1.update();
    enc1.update();

    //attachInterrupt(5, update, FALLING);
    //enc1.delta();
    //katana.update();
    effects.update();
    panels.update();

    panels.draw();
}
