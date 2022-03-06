#include "Renderer.h"
#include "utils.h"
#include "avr/pgmspace.h"
#include "Keys.h"

#define MAIN_SCREEN 1
#define CLOCK_SCREEN 0

static Arduino_ST7789 *gDisplay;
Scene* scenes;
static uint8_t __scenesCurrentIndex = 0;
static Scene* currentScene;

void handleButton1(ButtonState state);

void rendererSetup(Arduino_ST7789* display) {
    Serial.begin(9600);
    gDisplay = display;
    registerKeyHandler(handleButton1, 0);
    scenes = (Scene*) calloc(1, sizeof(Scene));
}

void render() {
    if (currentScene->show) {
        for (uint8_t i = 0; i < currentScene->__component_index; i++) {
            Component* cmp = (currentScene->components + i);
            if (cmp->update) {
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
    if (state == PRESSED) {
        setScene(1);
    }
}

void setScene(uint8_t sceneIndex)  {
    hideScene(currentScene);
    gDisplay->clearScreen();
    currentScene = &scenes[sceneIndex];
    for (int i = 0; i < currentScene->__component_index; i++) {
        (currentScene->components + i)->update = true;
    }
    showScene(currentScene);
}

uint8_t addScene(Scene scene) {
    if (__scenesCurrentIndex > 0) {
        scenes = (Scene*) realloc(scenes, sizeof(Scene) * (__scenesCurrentIndex + 1));  //Reallocate memory for components array
        if (scenes == NULL || scenes == nullptr) {
            Serial.println("Memory cannot be allocated");
        }
        Serial.println(__scenesCurrentIndex + 1);
    }
    scenes[__scenesCurrentIndex] = scene;
    return (__scenesCurrentIndex++);
}