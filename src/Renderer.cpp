#include "Renderer.h"
#include "Component.h"
#include "utils.h"
#include "avr/pgmspace.h"
#include "Keys.h"

#define BITMAP_SCANSIZE 2
#define SCALE_FACTOR 120

static Component logo;
static Arduino_ST7789 *gDisplay;

Component** components = (Component**) malloc(2);
static uint8_t componentIndex = 0;

static const uint16_t bitmap[] PROGMEM = {
    0xF30A, 0x5711,
    0x651D, 0xE521
};

void handleButton1(ButtonState state);

void rendererSetup(Arduino_ST7789* display) {
    Serial.begin(9600);
    gDisplay = display;
    registerKeyHandler(handleButton1, 0);
}

void render() {
    uint8_t length = *(&components + 1) - components;
    for (size_t i = 0; i < length; i++)
    {
        Component* cmp = components[i];
        if (!cmp->updated) {
          cmp->render(gDisplay);
          cmp->updated = true;
        }
    }
    
}

void drawLine(int x, int y, int length, uint8_t thickness, bool vertical, uint16_t color) {
    gDisplay->fillRect(x,y, vertical ? thickness : length, vertical ? length : thickness, color);
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

void addComponent(Component* component) {
  uint8_t length = *(&components + 1) - components;
  if (componentIndex + 1 >= length) {
    Component** cmps = (Component**) malloc(length + 1);
    for(uint8_t i = 0; i < length; i++) {
      cmps[i] = components[i];
    }
    cmps[++componentIndex] = component;
    free(components);
    components = cmps;
  } else {
    components[componentIndex++] = component;
  }
}

void handleButton1(ButtonState state) {
  gDisplay->fillRect(0, 0, DISPLAY_SIZE, DISPLAY_SIZE, BLUE);
}