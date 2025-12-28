#include "WatchMode.h"

void WatchMode::begin() {
    wifiMgr.startStationMode();
    // Assuming NTP is handled if wifi connected, or we manually trigger it
    // For now simple time placeholder
}

void WatchMode::stop() {
    wifiMgr.stopWiFi();
}

void WatchMode::update() {
    wifiMgr.update();
    
    // Basic connectivity check to sync time?
}

void WatchMode::draw() {
    displayMgr.clear();
    
    // Time
    char timeStr[10];
    sprintf(timeStr, "%02d:%02d", hour(), minute());
    displayMgr.drawText(30, 20, timeStr, 24);
    
    // Date
    char dateStr[20];
    sprintf(dateStr, "%02d/%02d/%04d", day(), month(), year());
    displayMgr.drawText(30, 45, dateStr, 10);
    
    // Status
    String status = (wifiMgr.getState() == WIFI_STATE_STA_CONNECTED) ? "WiFi: ON" : "WiFi: ...";
    displayMgr.drawStatus("Watch Mode", status);
    
    displayMgr.display();
}

void WatchMode::syncTime() {
    // TODO: implement NTP sync using NTPClient library
    // For now just relying on TimeLib
}
