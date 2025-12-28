#ifndef WATCH_MODE_H
#define WATCH_MODE_H

#include "Feature.h"
#include <TimeLib.h>
#include "../modules/WiFiManager.h"

class WatchMode : public Feature {
public:
    void begin() override;
    void update() override;
    void draw() override;
    void stop() override;

private:
    void syncTime();
    unsigned long lastSync = 0;
};

#endif
