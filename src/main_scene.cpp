#include "main_screen.h"
#include "Clock.h"
#include "Arduino.h"

#define __MAIN_SCREEN_PTR ((Scene*) get_element(&scenes, __mainScreenSceneIndex))

extern List scenes;
static uint8_t __mainScreenSceneIndex;

void renderStatusBar(Component* context, Arduino_ST7789* display) {
    drawLine(context->x, context->y, DISPLAY_SIZE, 3, false, WHITE);
}

void renderWelcomeMessage(Component* context, Arduino_ST7789* display) {
    display->setCursor(context->x, context->y);
    display->setTextColor(WHITE);
    display->setTextSize(3);
    display->print("WELCOME!");
}


void initMainScreen() {
    __mainScreenSceneIndex = addScene(create_scene());
    Component statusBar = createComponent(0, 20, renderStatusBar);
    Component clock = clockWidget(2, WHITE, WHITE, false);
    Component welcome = createComponent(50, 100, renderWelcomeMessage);
    clock.x = DISPLAY_SIZE - 60;
    clock.y = 20 - 16;
    registerClockWidget(clock.id);
    add_component(__MAIN_SCREEN_PTR, clock);
    add_component(__MAIN_SCREEN_PTR, statusBar);
    add_component(__MAIN_SCREEN_PTR, welcome);
}