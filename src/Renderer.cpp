#include "Renderer.h"
#include "Component.h"
#include "utils.h"
#include "avr/pgmspace.h"
#include "Keys.h"

#define BITMAP_SCANSIZE 2
#define SCALE_FACTOR 120

static Component logo;
static Arduino_ST7789* gDisplay;

static const uint16_t bitmap[] PROGMEM = {
    0xF30A, 0x5711,
    0x651D, 0xE521
};

void left(ButtonState state);
void right(ButtonState state);

void rendererSetup(Arduino_ST7789* display) {
    Serial.begin(9600);
    gDisplay = display;
    logo = createLogo(&createBitmap(bitmap, sizeof(bitmap) / sizeof(bitmap[0])), 64, 64, 0, 0);
    logo.visible = true;
    registerKeyHandler(left, FIRST_KEY);
    registerKeyHandler(right, SECOND_KEY);
}

static Vec2D direction = createVec2D(0, 0);

void render() {
    renderComponent(&logo);
}

void drawLine(int x, int y, int length, uint8_t thickness, bool vertical, uint16_t color) {
    gDisplay->fillRect(x,y, vertical ? thickness : length, vertical ? length : thickness, color);
}

void renderStatusBar() {
    drawLine(0, 20, 240, 2, false, WHITE);
}

void left(ButtonState state) {
  if (state == PRESSED) {
      direction.x = -10;
  } else if (state == RELEASED){
      direction.x = 0;
  }
}

void right(ButtonState state) {
  if (state == PRESSED) {
    direction.x = 10;
  } else if (state == RELEASED){
    direction.x = 0;
  }
}