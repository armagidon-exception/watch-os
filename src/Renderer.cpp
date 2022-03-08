#include "Renderer.h"
#include "utils.h"
#include "avr/pgmspace.h"
#include "Keys.h"

#define MAIN_SCREEN 1
#define CLOCK_SCREEN 0

static Arduino_ST7789 *gDisplay;
List scenes;
static uint8_t currentSceneIndex;

void handleButton1(ButtonState state);

void rendererSetup(Arduino_ST7789* display) {
    Serial.begin(9600);
    gDisplay = display;
    registerKeyHandler(handleButton1, 0);
    scenes = create_arraylist(1, sizeof(Scene));
}

void render() {
    Scene* currentScene = (Scene*) get_element(&scenes, currentSceneIndex);
    if (currentScene->show) {
        for_each(&currentScene->components, [](void* element) {
            Component* cmp = (Component*) element;
            if (cmp->update) {
                cmp->render(cmp, gDisplay);
                cmp->update = false;
            }
        });
    }
}

void drawLine(int x, int y, int length, uint8_t thickness, bool vertical, uint16_t color) {
    gDisplay->fillRect(x,y, vertical ? thickness : length, vertical ? length : thickness, color);
}

void handleButton1(ButtonState state) {
    if (state == PRESSED) {
        if (currentSceneIndex == 0)
            setScene(1);
        else
            setScene(0);
    }
}

void setScene(uint8_t sceneIndex)  {
    Scene* s = (Scene*) get_element(&scenes, currentSceneIndex);
    hideScene(s);
    gDisplay->clearScreen();
    currentSceneIndex = sceneIndex;
    for_each(&s->components, [](void* context) {
        Component* ptr = (Component*) context;
        ptr->update = true;
    });
    s = (Scene*) get_element(&scenes, currentSceneIndex);
    showScene(s);
}

uint8_t addScene(Scene scene) {
    if (scenes.__element_head > scenes.__initial_capacity - 1) {
        scenes.array = realloc(scenes.array, scenes.__element_size * (scenes.__element_head + 1));  //Reallocate memory for components array
    }
    ((Scene*) scenes.array)[scenes.__element_head++] = scene; //Add new component
    return (scenes.__element_head - 1);
}

Component* findComponentById(uint8_t id) {
    for (uint8_t i = 0; i < scenes.__element_head; i++) {
        Scene* scene = (Scene*) get_element(&scenes, i);
        for (uint8_t k = 0; k < scene->components.__element_head; k++) {
            Component* cmp = (Component*) get_element(&scene->components, k);
            if (cmp->id == id) {
                return cmp;
            }
        }
    }
    return nullptr;
}