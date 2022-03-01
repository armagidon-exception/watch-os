#include "Clock.h"
#include "Component.h"
#include "Renderer.h"
#define CLOCK_SCALE 6
#define CLOCK_X DISPLAY_SIZE / 2 - 15 * CLOCK_SCALE
#define CLOCK_Y DISPLAY_SIZE / 2 - 8 * CLOCK_SCALE

static volatile uint8_t seconds = 0;
static volatile uint8_t minutes = 0;
static volatile uint8_t hours = 0;

static unsigned long timeStump = millis();
static Component clock;

void tickClock() {
    bool update = false;
    if (millis() - timeStump >= 1000) {
        seconds++;
        timeStump = millis();
    }
    if (seconds >= 60) {
        update = true;
        seconds = 0;
        minutes++;
    }
    if (minutes >= 60) {
        hours++;
        minutes=0;
        update = true;
    }
    if (update) {
        clock.updated = false;
    }
}

void renderClock(Arduino_ST7789 *display) {
    display->fillRect(CLOCK_X, CLOCK_Y, 30 * CLOCK_SCALE, 8 * CLOCK_SCALE, WHITE);
    display->setCursor(CLOCK_X, CLOCK_Y);
    display->setTextSize(CLOCK_SCALE);
    display->setTextColor(BLACK);
    display->setTextWrap(false);
    char* s = (char*) malloc(5);
    sprintf(s, "%02d:%02d", hours, minutes);
    display->print(s);
    free(s);
}

void initializeClock() {
    clock.render = renderClock;
    clock.updated = false;
    addComponent(&clock);
}