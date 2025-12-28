#include "NRFManager.h"

NRFManager nrfMgr;

NRFManager::NRFManager() : radio(PIN_NRF_CE, PIN_NRF_CSN) {
    initialized = false;
}

bool NRFManager::begin() {
    // VSPI pins are standard on ESP32, but we can enforce them if needed via SPI.begin()
    // RF24 uses global SPI by default. 
    // If we needed custom pins: SPI.begin(SCK, MISO, MOSI, CSN);
    // But platformio config handles standard usually.
    
    if (!radio.begin()) {
        return false;
    }
    
    radio.setPALevel(RF24_PA_MAX); // High power
    radio.setDataRate(RF24_1MBPS);
    initialized = true;
    return true;
}

void NRFManager::scanChannels(uint8_t* results, int size) {
    if (!initialized) return;
    
    radio.setAutoAck(false);
    
    for (int i = 0; i < size && i < 128; i++) {
        radio.setChannel(i);
        radio.startListening();
        delayMicroseconds(128);
        radio.stopListening();
        if (radio.testCarrier()) {
             results[i]++;
        }
    }
}

void NRFManager::startListening() {
    if (!initialized) return;
    radio.startListening();
}

bool NRFManager::available() {
    if (!initialized) return false;
    return radio.available();
}

void NRFManager::read(void* buffer, uint8_t size) {
    if (!initialized) return;
    radio.read(buffer, size);
}

RF24* NRFManager::getDriver() {
    return &radio;
}
