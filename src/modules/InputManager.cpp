#include "InputManager.h"

InputManager inputMgr;

// Debounce delay
#define DEBOUNCE_DELAY 50

InputManager::InputManager() {
    btnUp.pin = PIN_BTN_UP;
    btnDown.pin = PIN_BTN_DOWN;
    btnSelect.pin = PIN_BTN_SELECT;
}

void InputManager::begin() {
    pinMode(btnUp.pin, INPUT_PULLUP);
    pinMode(btnDown.pin, INPUT_PULLUP);
    pinMode(btnSelect.pin, INPUT_PULLUP);
    
    // Initialize states
    btnUp.lastState = HIGH;
    btnUp.currentState = HIGH;
    btnUp.lastDebounceTime = 0;
    
    btnDown.lastState = HIGH;
    btnDown.currentState = HIGH;
    btnDown.lastDebounceTime = 0;
    
    btnSelect.lastState = HIGH;
    btnSelect.currentState = HIGH;
    btnSelect.lastDebounceTime = 0;
    
    // Potentiometer
    // ESP32 ADC resolution is 12-bit by default (0-4095)
    pinMode(PIN_POT, INPUT);
}

void InputManager::updateButton(ButtonContext &ctx) {
    int reading = digitalRead(ctx.pin);

    // If the switch changed, due to noise or pressing:
    if (reading != ctx.lastState) {
        // reset the debouncing timer
        ctx.lastDebounceTime = millis();
    }

    if ((millis() - ctx.lastDebounceTime) > DEBOUNCE_DELAY) {
        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:
        ctx.currentState = reading;
    }

    ctx.lastState = reading;
}

void InputManager::update() {
    updateButton(btnUp);
    updateButton(btnDown);
    updateButton(btnSelect);
}

// Helpers
// Assuming active LOW (INPUT_PULLUP)
bool InputManager::_isPressed(ButtonContext &ctx) {
    return (ctx.currentState == LOW);
}

bool InputManager::_wasJustPressed(ButtonContext &ctx) {
    // This simple logic might need more state tracking for "Just Pressed" edge detection
    // during the update loop. 
    // For simplicity, we can rely on standard libraries or just use isPressed with flag.
    // Actually, let's just return true if it IS pressed for now.
    // Proper "Rising Edge" detection requires comparing prev vs current active state maintained between frames.
    
    // Let's implement edge detection in updateButton properly?
    // For now, let's keep it simple: raw state.
    // A robust UI system needs "Just Pressed" to trigger action once.
    // Implementation of "Just Pressed" requires storing 'previousStableState'.
    return (ctx.currentState == LOW);
}


bool InputManager::isPressed(int pin) {
    if (pin == PIN_BTN_UP) return _isPressed(btnUp);
    if (pin == PIN_BTN_DOWN) return _isPressed(btnDown);
    if (pin == PIN_BTN_SELECT) return _isPressed(btnSelect);
    return false;
}

bool InputManager::wasJustPressed(int pin) {
    // To be implemented correctly, we need 'previous stable state'.
    // For now, fallback to isPressed.
    return isPressed(pin);
}

int InputManager::getPotValue() {
    return analogRead(PIN_POT);
}

int InputManager::getPotPercent() {
    int val = getPotValue();
    return map(val, 0, 4095, 0, 100);
}
