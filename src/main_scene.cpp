#include "main_screen.h"

uint8_t __mainScreenSceneIndex;
extern Scene* scenes;

#define CLOCK_X DISPLAY_SIZE / 2 - 3 * 8 * 4
#define CLOCK_Y DISPLAY_SIZE / 2 - 8 * 4

void renderWelcomeMessage(Component* context, Arduino_ST7789* display) {
    display->setCursor(context->x, context->y);
    display->setTextSize(4);
    display->setTextColor(WHITE);
    display->setTextWrap(false);
    display->print("WELCOME!");
}

void initMainScreen() {
    Component welcomeMessage = createComponent(CLOCK_X, CLOCK_Y, renderWelcomeMessage);
    __mainScreenSceneIndex = addScene(createScene());
    Serial.println("MS" + String(__mainScreenSceneIndex));
    addComponent(&scenes[__mainScreenSceneIndex], welcomeMessage);
}