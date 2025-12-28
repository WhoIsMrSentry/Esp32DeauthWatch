#include <Arduino.h>
#include "config.h"

// Modules
#include "modules/DisplayManager.h"
#include "modules/InputManager.h"
#include "modules/WiFiManager.h"
#include "modules/NRFManager.h"
#include "modules/AttackEngine.h"

// Features
#include "features/WatchMode.h"
#include "features/MenuMode.h"
#include "features/PhishingMode.h"
#include "features/AttackMode.h"
#include "features/NRFMode.h"

// Global Instances
WatchMode watchMode;
MenuMode menuMode;
PhishingMode phishingMode;
AttackMode attackMode;
NRFMode nrfMode;

Feature* currentFeature = nullptr;

void changeFeature(FeatureType ft) {
    if (currentFeature) {
        currentFeature->stop();
    }
    
    switch(ft) {
        case FEATURE_WATCH: currentFeature = &watchMode; break;
        case FEATURE_MENU: currentFeature = &menuMode; break;
        case FEATURE_PHISHING: currentFeature = &phishingMode; break;
        case FEATURE_ATTACK: currentFeature = &attackMode; break;
        case FEATURE_NRF: currentFeature = &nrfMode; break;
    }
    
    if (currentFeature) {
        currentFeature->begin();
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("Booting ESP32 SmartWatch...");
    
    // Hardware Init
    inputMgr.begin();
    displayMgr.begin();
    wifiMgr.begin();
    // NRF Init is done in NRFMode features usually, but can be done here too
    // nrfMgr.begin(); 
    
    pinMode(PIN_LED, OUTPUT);
    
    // Start with Watch Mode
    changeFeature(FEATURE_WATCH);
}

void loop() {
    // Global Updates
    inputMgr.update();
    
    // Special Global Override: If Select + Up + Down are pressed -> Reboot or Menu?
    // For now, rely on Feature to handle exit or Button combos
    // Example: Long press Select -> Menu in WatchMode (handled inside WatchMode/MenuMode logic)
    // But since WatchMode doesn't have "Select" logic implemented yet for Menu, let's add a global override
    
    /* 
    if (inputMgr.isPressed(PIN_BTN_SELECT) && inputMgr.isPressed(PIN_BTN_UP)) {
        changeFeature(FEATURE_MENU);
        delay(500); 
    }
    */
   
    if (currentFeature) {
        currentFeature->update();
        currentFeature->draw();
    }
    
    delay(10);
}
