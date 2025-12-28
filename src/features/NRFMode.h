#ifndef NRF_MODE_H
#define NRF_MODE_H

#include "Feature.h"
#include "../modules/NRFManager.h"

class NRFMode : public Feature {
public:
    void begin() override;
    void update() override;
    void draw() override;
    void stop() override;

private:
    uint8_t channels[128];
};

#endif
