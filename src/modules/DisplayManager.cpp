#include "DisplayManager.h"

DisplayManager displayMgr;

DisplayManager::DisplayManager() {
    displayDriver = new SSD1306Wire(OLED_ADDR, PIN_SDA, PIN_SCL);
}

void DisplayManager::begin() {
    displayDriver->init();
    displayDriver->flipScreenVertically();
    displayDriver->setFont(ArialMT_Plain_10);
    displayDriver->drawString(0, 0, "Booting...");
    displayDriver->display();
}

void DisplayManager::clear() {
    displayDriver->clear();
}

void DisplayManager::display() {
    displayDriver->display();
}

void DisplayManager::drawText(int x, int y, String text, int fontSize) {
    if (fontSize == 16) {
        displayDriver->setFont(ArialMT_Plain_16);
    } else if (fontSize == 24) {
        displayDriver->setFont(ArialMT_Plain_24);
    } else {
        displayDriver->setFont(ArialMT_Plain_10);
    }
    displayDriver->drawString(x, y, text);
}

void DisplayManager::drawStatus(String title, String status) {
    displayDriver->setFont(ArialMT_Plain_10);
    displayDriver->setTextAlignment(TEXT_ALIGN_LEFT);
    displayDriver->drawString(0, 0, title);
    
    displayDriver->drawLine(0, 12, 128, 12);
    
    displayDriver->setFont(ArialMT_Plain_10);
    displayDriver->drawStringMaxWidth(0, 15, 128, status);
}

void DisplayManager::drawMenu(String title, const char** items, int itemCount, int selectedIndex) {
    clear();
    displayDriver->setFont(ArialMT_Plain_10);
    displayDriver->setTextAlignment(TEXT_ALIGN_CENTER);
    displayDriver->drawString(64, 0, title);
    displayDriver->drawLine(0, 12, 128, 12);
    
    displayDriver->setTextAlignment(TEXT_ALIGN_LEFT);
    
    int startY = 15;
    int lineHeight = 12;
    
    // Simple scrolling logic can be added later if needed
    // For now, show 3 items centered around selected
    
    for (int i = 0; i < itemCount; i++) {
        int y = startY + (i * lineHeight);
        if (y > 54) break; // Clip
        
        if (i == selectedIndex) {
            displayDriver->fillRect(0, y, 128, lineHeight);
            displayDriver->setColor(BLACK);
            displayDriver->drawString(2, y, "> " + String(items[i]));
            displayDriver->setColor(WHITE);
        } else {
            displayDriver->drawString(2, y, "  " + String(items[i]));
        }
    }
    display();
}

SSD1306Wire* DisplayManager::getDriver() {
    return displayDriver;
}
