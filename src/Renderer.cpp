#include "Renderer.h"
#include "Component.h"
#include "utils.h"
#include <Arduino.h>

#define BITMAP_SCANSIZE 2
#define SCALE_FACTOR 120

static Component logo;
extern Display display;
static const uint16_t bitmap[] PROGMEM = {
    0xF30A, 0x5711,
    0x651D, 0xE521
};

void rendererSetup() {
    Serial.begin(9600);
    clearScreen();
    logo = createLogo(&createBitmap(bitmap, sizeof(bitmap) / sizeof(bitmap[0])), 64, 64, 0, 0);
    logo.visible = true;
    logo.position.x = DISPLAY_SIZE - 64;
    pinMode(4, INPUT);
    pinMode(5, INPUT);
}

static Vec2D direction = createVec2D(-2, 0);
void render() {
    if (logo.position.x == 0) {
        direction.x = 2;    
    } else if(logo.position.x + logo.size.width >= DISPLAY_SIZE) {
        direction.x = -2;
    }
    moveComponent(&logo, &direction);
}

void drawLine(int x, int y, int length, uint8_t thickness, bool vertical, uint16_t color) {
    fillArea(&createVec2D(x, y), &createDimension(vertical ? thickness : length, vertical ? length : thickness), color);
}

void renderStatusBar() {
    drawLine(0, 20, DISPLAY_SIZE, 2, false, WHITE);
}