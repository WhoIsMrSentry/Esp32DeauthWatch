#ifndef FEATURE_H
#define FEATURE_H

#include <Arduino.h>
#include "../modules/DisplayManager.h"
#include "../modules/InputManager.h"

class Feature {
public:
    virtual void begin() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    
    // Optional
    virtual void stop() {}
};

#endif
