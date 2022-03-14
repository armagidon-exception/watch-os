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

Component createComponent(int x, int y, RendererCallback renderMethod) {
    Component cmp = {x, y, renderMethod, true, findFreeId(), nullptr, false, false, CUSTOM};
    if (cmp.id == -1) {
        Serial.println("Could not find free id");
    }
    return cmp;
}

void highlightComponent(Component* cmp) {
    cmp->highlighted = true;
    cmp->update = true;
}

void dehighlightComponent(Component* cmp) {
    cmp->highlighted = false;
    cmp->update = true;
}