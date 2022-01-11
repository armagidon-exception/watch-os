#include "Renderer.h"
#include "Component.h"
#include "utils.h"
#include <Arduino.h>
#include "Keys.h"

#define BITMAP_SCANSIZE 2
#define SCALE_FACTOR 120

static Component logo;
extern Display display;
static const uint16_t bitmap[] PROGMEM = {
    0xF30A, 0x5711,
    0x651D, 0xE521
};

void left(ButtonState state);
void right(ButtonState state);

void rendererSetup() {
    Serial.begin(9600);
    clearScreen();
    logo = createLogo(&createBitmap(bitmap, sizeof(bitmap) / sizeof(bitmap[0])), 64, 64, 0, 0);
    logo.visible = true;
    logo.position.x = DISPLAY_SIZE - 64;
    registerKeyHandler(left, FIRST_KEY);
    registerKeyHandler(right, SECOND_KEY);
}

static Vec2D direction = createVec2D(0, 0);

void render() {
    //renderComponent(&logo);
}

void drawLine(int x, int y, int length, uint8_t thickness, bool vertical, uint16_t color) {
    fillArea(&createVec2D(x, y), &createDimension(vertical ? thickness : length, vertical ? length : thickness), color);
}

void renderStatusBar() {
    drawLine(0, 20, DISPLAY_SIZE, 2, false, WHITE);
}

void left(ButtonState state) {
  if (state == PRESSED) {
      direction.x = -10;
      moveComponent(&logo, &direction);
  }
}

void right(ButtonState state) {
  if (state == PRESSED) {
    direction.x = 10;
    moveComponent(&logo, &direction);
  }
}