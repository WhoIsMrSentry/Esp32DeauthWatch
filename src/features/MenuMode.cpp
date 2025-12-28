#include "MenuMode.h"

void MenuMode::begin() {
    selectedIndex = 0;
}

void MenuMode::update() {
    handleInput();
}

void MenuMode::handleInput() {
    inputMgr.update();
    
    if (inputMgr.wasJustPressed(PIN_BTN_DOWN)) {
        selectedIndex++;
        if (selectedIndex >= menuCount) selectedIndex = 0;
    }
    
    if (inputMgr.wasJustPressed(PIN_BTN_UP)) {
        selectedIndex--;
        if (selectedIndex < 0) selectedIndex = menuCount - 1;
    }
    
    // Potentiometer Navigation Override (Optional)
    // int pot = inputMgr.getPotPercent();
    // selectedIndex = map(pot, 0, 100, 0, menuCount - 1);
    
    if (inputMgr.wasJustPressed(PIN_BTN_SELECT)) {
        switch(selectedIndex) {
            case 0: changeFeature(FEATURE_PHISHING); break;
            case 1: changeFeature(FEATURE_ATTACK); break;
            case 2: changeFeature(FEATURE_NRF); break;
            case 3: changeFeature(FEATURE_WATCH); break;
        }
    }
}

void MenuMode::draw() {
    displayMgr.drawMenu("Main Menu", menuItems, menuCount, selectedIndex);
}
