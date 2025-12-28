#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "config.h"
#include <WiFi.h>
#include <DNSServer.h>

enum WiFiState {
    WIFI_STATE_OFF,
    WIFI_STATE_STA_CONNECTING,
    WIFI_STATE_STA_CONNECTED,
    WIFI_STATE_AP_MODE
};

class MyWiFiManager { // Avoid conflict with standard libraries
public:
    MyWiFiManager();
    void begin();
    void update();
    
    void startStationMode();
    void startAPMode();
    void stopWiFi();
    
    WiFiState getState();
    String getIP();
    
    // For captive portal
    DNSServer* getDNSServer();

private:
    WiFiState currentState;
    DNSServer dnsServer;
};

extern MyWiFiManager wifiMgr;

#endif
