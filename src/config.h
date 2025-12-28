#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// --- Hardware Pins ---

// OLED Display (I2C)
#define PIN_SDA 21
#define PIN_SCL 22
#define OLED_ADDR 0x3C

// Buttons
#define PIN_BTN_UP 13
#define PIN_BTN_DOWN 14
#define PIN_BTN_SELECT 12
//#define PIN_BTN_BACK 0 // Optional

// Potentiometer
// ADC1_CHANNEL_6 is GPIO 34
#define PIN_POT 34 

// NRF24L01 (VSPI)
#define PIN_NRF_CE 4
#define PIN_NRF_CSN 5
#define PIN_NRF_SCK 18
#define PIN_NRF_MISO 19
#define PIN_NRF_MOSI 23

// Onboard LED
#define PIN_LED 2

// --- Network Settings ---
#define DEFAULT_SSID "ESP32_SmartWatch"
#define DEFAULT_PASS "password123"

// --- Phishing Settings ---
#define PHISHING_SSID "Free_WiFi"
#define PHISHING_DOMAIN "www.google.com" 

enum FeatureType {
    FEATURE_WATCH,
    FEATURE_MENU,
    FEATURE_PHISHING,
    FEATURE_ATTACK,
    FEATURE_NRF
};

void changeFeature(FeatureType ft);

#endif
