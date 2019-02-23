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
RotaryEncoder enc1 = RotaryEncoder(2, 3);
RotaryEncoder enc2 = RotaryEncoder(18, 19);
RotaryEncoder enc3 = RotaryEncoder(20, 21);

Effects effects(&katana);
EffectPanel effectPanel(&sw3, &sw1, &sw2, &enc1, &enc2, &enc3);
EffectListPanel effectListPanel(&sw1, &enc1);
SlotListPanel slotListPanel(&sw1, &enc1, (EffectSlot**)effects.slots, 3);

Panels panels(&effects, &effectPanel, &effectListPanel, &slotListPanel, &homeSwitch);

void setup()
{
    panels.setup();

    Serial.begin(115200);
    midi.setup();

    pinMode(22, INPUT_PULLUP);
    sw1.attach(22);
    sw1.interval(5);

    /*pinMode(23, INPUT_PULLUP);
    sw2.attach(23);
    sw2.interval(5);

    pinMode(24, INPUT_PULLUP);
    sw3.attach(24);
    sw3.interval(5);
*/
    /*pinMode(25, INPUT_PULLUP);
    sw4.attach(25);
    sw4.interval(5);*/

    panels.showEffect();

    Serial.println(F("Initialized"));
    delay(5000);

    katana.init();
}

//void printf()
void loop()
{
    sw1.update();
    //sw2.update();
    //sw3.update();
    //sw4.update();

    katana.update();
    effects.update();
    panels.update();

    panels.draw();
    //char buf[100];
    //sprintf(buf, "%ld %ld",enc1.delta(), enc1.value());
    //Serial.println(buf);
}
