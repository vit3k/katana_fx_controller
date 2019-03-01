#ifndef H_EFFECTLISTPANEL
#define H_EFFECTLISTPANEL

#include "listPanel.h"
#include "effects/effectSlot.h"
#include <Bounce2.h>
#include "rotaryEncoder.h"

class EffectListPanel : public ListPanel {
protected:
    virtual String* list();
    virtual byte listCount();
    virtual void onSelect();
    virtual void onChange();
    EffectSlot* effectSlot;
    String* names;
public:
    EffectListPanel(Bounce* select, RotaryEncoder* change):
        ListPanel(change, select) {}

    void show(EffectSlot* effectSlot);
};

#endif