#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "config.h"

enum ButtonState {
    BTN_RELEASED,
    BTN_PRESSED,
    BTN_JUST_PRESSED,
    BTN_JUST_RELEASED
};

class InputManager {
public:
    InputManager();
    void begin();
    void update();
    
    // Check specific buttons
    bool isPressed(int pin);
    bool wasJustPressed(int pin);
    
    // Potentiometer
    int getPotValue();
    int getPotPercent(); // 0-100

private:
    struct ButtonContext {
        int pin;
        bool lastState;       // Physical state
        bool currentState;    // Physical state
        unsigned long lastDebounceTime;
    };
    
    ButtonContext btnUp;
    ButtonContext btnDown;
    ButtonContext btnSelect;
    
    // Helper to update individual button context
    void updateButton(ButtonContext &ctx);
    
    // Provide state query for a context
    bool _isPressed(ButtonContext &ctx);
    bool _wasJustPressed(ButtonContext &ctx);
};

extern InputManager inputMgr;

#endif
