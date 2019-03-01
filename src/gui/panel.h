#ifndef H_PANEL
#define H_PANEL

#include <U8g2lib.h>

class Panels;

class Panel {
protected:
    Panels* panels;
public:
    virtual void draw(U8G2* lcd);
    virtual void update();
    void setPanels(Panels* panels) {
        this->panels = panels;
    }
};

#endif