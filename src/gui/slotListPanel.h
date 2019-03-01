#ifndef H_SLOTLISTPANEL
#define H_SLOTLISTPANEL

#include "listPanel.h"
#include <Bounce2.h>
#include "rotaryEncoder.h"
#include "effects/effectSlot.h"

class SlotListPanel : public ListPanel {
protected:
    virtual String* list();
    virtual byte listCount();
    virtual void onSelect();
    EffectSlot** slots;
    byte slotsCount;
    String* names;
    Bounce* onoffSwitch;
public:
    SlotListPanel(Bounce* select, RotaryEncoder* change, EffectSlot** slots, byte slotsCount, Bounce* onoffSwitch):
        ListPanel(change, select), slots(slots), slotsCount(slotsCount), onoffSwitch(onoffSwitch)
    {
        names = new String[slotsCount];
        for(byte i = 0; i < slotsCount; i++) {
            names[i] = slots[i]->name;
        }
    }
    ~SlotListPanel()
    {
        delete[] names;
    }
    void update();
};
#endif