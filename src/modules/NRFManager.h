#ifndef NRF_MANAGER_H
#define NRF_MANAGER_H

#include "config.h"
#include <RF24.h>

class NRFManager {
public:
    NRFManager();
    bool begin();
    
    // Basic Scanner
    void scanChannels(uint8_t* results, int size);
    
    // Sniff
    void startListening();
    bool available();
    void read(void* buffer, uint8_t size);
    
    RF24* getDriver();

private:
    RF24 radio;
    bool initialized;
};

extern NRFManager nrfMgr;

#endif
