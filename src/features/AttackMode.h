#ifndef ATTACK_MODE_H
#define ATTACK_MODE_H

#include "Feature.h"
#include "../modules/AttackEngine.h"

class AttackMode : public Feature {
public:
    void begin() override;
    void update() override;
    void draw() override;
    void stop() override;

private:
    int state = 0; // 0=Scan, 1=AttackMenu, 2=Deauthing
    
    int selectedIndex = 0;
    int apCount = 0;
    // Simple mock list for now, ideally filled by Scan
    String apList[10]; 
    uint8_t apBssids[10][6];
    
    void performScan();
    void handleInput();
};

#endif
