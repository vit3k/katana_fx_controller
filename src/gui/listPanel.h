#ifndef H_LISTPANEL
#define H_LISTPANEL

#include "panel.h"
#include <Bounce2.h>
#include "rotaryEncoder.h"

class ListPanel : public Panel {
protected:
    virtual String* list() = 0;
    virtual byte listCount() = 0;
    virtual void onChange() {}
    virtual void onSelect() {}

    Bounce* select;
    RotaryEncoder* change;
    byte current = 0;
    byte firstVisible = 0;
public:
    void init();
    void draw(U8G2* lcd);
    void update();
    ListPanel(RotaryEncoder* change, Bounce* select)
        : select(select), change(change) {}
};

#endif