#include "Renderer.h"
#include "utils.h"
#include "avr/pgmspace.h"
#include "Keys.h"

#define MAIN_SCREEN 1
#define CLOCK_SCREEN 0

static Arduino_ST7789 *gDisplay;
Scene* scenes;
static uint8_t __sceneIndex = 0;
static Scene* currentScene;

void handleButton1(ButtonState state);

void rendererSetup(Arduino_ST7789* display) {
    Serial.begin(9600);
    gDisplay = display;
    registerKeyHandler(handleButton1, 0);
    scenes = (Scene*) malloc(sizeof(Scene));
}

void render() {
    if (currentScene->show) {
        for (uint8_t i = 0; i < currentScene->__component_index; i++) {
            Component* cmp = (currentScene->components + i);
            if (cmp->update) {
                if (currentScene == &scenes[0]) {
                    Serial.println("rc");
                }
                cmp->render(cmp, gDisplay);
                cmp->update = false;
            }
        }
    }
}

void drawLine(int x, int y, int length, uint8_t thickness, bool vertical, uint16_t color) {
    gDisplay->fillRect(x,y, vertical ? thickness : length, vertical ? length : thickness, color);
}

void handleButton1(ButtonState state) {
    Serial.println(__sceneIndex);
    if (currentScene == &scenes[0])
        setScene(1);
    else
        setScene(0);
}

void setScene(uint8_t sceneIndex)  {
    currentScene->show = false;
    gDisplay->clearScreen();
    currentScene = scenes + sceneIndex;
    for (int i = 0; i < currentScene->__component_index; i++) {
        (currentScene->components + i)->update = true;
    }
    currentScene->show = true;
}

uint8_t addScene(Scene scene) {
    if (__sceneIndex > 0) {
        realloc(scenes, sizeof(Scene) * (__sceneIndex + 2));  //Reallocate memory for components array
    }
    scenes[__sceneIndex] = scene; //Add new component
    return (__sceneIndex++);
}