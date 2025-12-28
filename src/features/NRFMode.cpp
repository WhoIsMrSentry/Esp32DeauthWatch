#include "NRFMode.h"

void NRFMode::begin() {
    nrfMgr.begin();
    memset(channels, 0, 128);
}

void NRFMode::stop() {
}

void NRFMode::update() {
    inputMgr.update();
    
    // Perform scan
    nrfMgr.scanChannels(channels, 128);
    
    if (inputMgr.wasJustPressed(PIN_BTN_SELECT) || inputMgr.getPotPercent() < 5) {
        changeFeature(FEATURE_MENU);
    }
}

void NRFMode::draw() {
    displayMgr.clear();
    displayMgr.drawStatus("NRF Scanner", "2.4GHz Spectrum");
    
    // Draw Graph
    // 128 channels, 128 pixels wide
    for (int i = 0; i < 128; i++) {
        int val = channels[i];
        if (val > 0) {
            int h = val * 5; // Scale
            if (h > 50) h = 50;
            displayMgr.getDriver()->drawLine(i, 63, i, 63 - h);
            
            // Decay
            if (channels[i] > 0) channels[i]--;
        }
    }
    
    displayMgr.display();
}
