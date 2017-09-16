#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "knob.h"
#include "midi.h"
#include <Bounce2.h>
#include "katana.h"
#include "effects.h"
#include "panels.h"

U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI lcd(U8G2_R0, 49, 48, 47);

USB usb;
Midi::Midi midi(&usb);
Katana katana(&midi);

Bounce sw1 = Bounce();
Bounce sw2 = Bounce();
Bounce sw3 = Bounce();
Bounce sw4 = Bounce();


EffectPanel effectPanel(&sw4, &sw2);
EffectListPanel effectListPanel(&sw2, &sw3, &sw1);
Panels panels(&effectPanel, &effectListPanel);

void setup()
{

    lcd.begin();
    Serial.begin(115200);
    if (usb.Init() == -1) {
        while (1);
    }
    delay( 200 );

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

    effectPanel.show(&booster);

    panels.show(&effectPanel);
    Serial.println("Initialized");
}


void loop()
{
    sw1.update();
    sw2.update();
    sw3.update();
    sw4.update();

    usb.Task();
    if ( usb.getUsbTaskState() == USB_STATE_RUNNING )
    {
        katana.poll();

    }
    panels.update();
    lcd.firstPage();
    do {
        panels.draw(lcd);

    } while ( lcd.nextPage() );
}
