#include "component.h"

static bool ids[16];

static uint8_t findFreeId() {
    for (uint8_t i = 0; i < sizeof(ids); i++) {
        if (!ids[i]) {
            ids[i] = true;
            return i;
        }
    }
    return -1;
}

Component createComponent(int x, int y, void (*renderMethod)(Component*, Arduino_ST7789* renderer)) {
    Component cmp = {x, y, renderMethod, true, findFreeId()};
    if (cmp.id == -1) {
        Serial.println("Could not find free id");
    }
    return cmp;
}