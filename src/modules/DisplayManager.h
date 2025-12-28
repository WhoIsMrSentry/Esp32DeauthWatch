#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "config.h"
#include <SSD1306Wire.h>

class DisplayManager {
public:
    DisplayManager();
    void begin();
    void clear();
    void display();
    void drawText(int x, int y, String text, int fontSize = 10);
    void drawStatus(String title, String status);
    void drawMenu(String title, const char** items, int itemCount, int selectedIndex);
    
    // Low level access
    SSD1306Wire* getDriver();

private:
    SSD1306Wire* displayDriver;
};

extern DisplayManager displayMgr;

#endif
