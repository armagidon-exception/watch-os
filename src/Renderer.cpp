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

void renderClock(int minutes, int hours, uint8_t x, uint8_t y, uint8_t scale);

void rendererSetup(Arduino_ST7789* display) {
    Serial.begin(9600);
    gDisplay = display;
}

void render() {
    
}

void drawLine(int x, int y, int length, uint8_t thickness, bool vertical, uint16_t color) {
    gDisplay->fillRect(x,y, vertical ? thickness : length, vertical ? length : thickness, color);
}

void clock(uint8_t hours, uint8_t minutes) {
  renderClock(minutes, hours, (240 - 5*6*6) / 2, 120 - 6 * 8 / 2, 6);
}

void renderClock(int minutes, int hours, uint8_t x, uint8_t y, uint8_t scale) {
    gDisplay->fillRect(x, y, 30 * scale, 8 * scale, WHITE);
    gDisplay->setCursor(x, y);
    gDisplay->setTextSize(scale);
    gDisplay->setTextColor(BLACK);
    gDisplay->setTextWrap(false);
    char* s = (char*) malloc(5);
    sprintf(s, "%02d:%02d", hours, minutes);
    gDisplay->print(s);
    free(s);
}