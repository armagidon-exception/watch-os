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
    for(uint8_t i = 0; i < 3; i++) {
        registerKeyHandler([](ButtonState state, uint8_t keyCode) {
            Scene* s = (Scene*) get_element(&scenes,  currentSceneIndex);
            if (s->keyCallbacks[keyCode] != nullptr)
                s->keyCallbacks[keyCode](state, keyCode);
        }, i);
    }

    showScene(s);
}

void add_scene(Scene scene) {
    add_element_with_id(&scenes, &scene, scene.id);
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