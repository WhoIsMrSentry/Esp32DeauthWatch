#ifndef MENU_MODE_H
#define MENU_MODE_H

#include "Feature.h"

class MenuMode : public Feature {
public:
    void begin() override;
    void update() override;
    void draw() override;

private:
    int selectedIndex = 0;
    const char* menuItems[4] = {
        "Phishing Portal",
        "WiFi Attacks",
        "NRF24 Sniffer",
        "Back to Watch"
    };
    int menuCount = 4;
    
    void handleInput();
};

#endif
