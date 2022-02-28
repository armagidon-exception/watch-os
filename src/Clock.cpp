#include "Clock.h"

static volatile uint8_t seconds = 0;
static volatile uint8_t minutes = 0;
static volatile uint8_t hours = 0;

static unsigned long timeStump = millis();

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
        //clock(hours, minutes);
    }
    
}