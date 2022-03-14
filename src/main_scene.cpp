#include "main_screen.h"
#include "Clock.h"
#include "utils.h"
#include "Arduino.h"
#include "button.h"

#define __MAIN_SCREEN_PTR ((Scene*) get_element(&scenes, __mainScreenSceneIndex))

typedef struct ArrowShape {
    bool inverted;
    uint8_t size;
} ArrowShape;

extern List scenes;
static uint8_t __mainScreenSceneIndex;

void renderArrow(Component* context, Arduino_ST7789* display)
{
    ArrowShape* shape = (ArrowShape*) context->customData + sizeof(ButtonData);
    //Verticies
    uint8_t x1 = context->x, x2 = context->x + (shape->inverted ? -10: 10) * shape->size, x3 = context->x + (shape->inverted ? -10 : 10) * shape->size;
    uint8_t y1 = context->y, y2 = context->y + 10 * shape->size, y3 = context->y - 10 * shape->size;
    uint8_t rxmin = min(x1, x2),
                rymin = min(y1, min(y2, y3)),
                rxmax = max(x1, x2),
                rymax = max(y1, max(y2, y3));
    if (!context->highlighted) {
        display->fillRect(rxmin, rymin, rxmax - rxmin, rymax - rymin, BLACK);
        display->fillTriangle(x1, y1, x2, y2, x3, y3, WHITE);
    } else {
        display->fillRect(rxmin, rymin, rxmax - rxmin, rymax - rymin, WHITE);
        display->fillTriangle(x1, y1, x2, y2, x3, y3, BLACK);
    }
}

Component createArrow(Vec2D pos, bool inverted, uint8_t size) {
    Component component = create_button(pos, renderArrow, [](Component* context) {
        Component* box = findComponentById(0);
        ArrowShape* shape = (ArrowShape*) context->customData + sizeof(ButtonData);
        box->update = true;
    });
    component.customData = realloc(component.customData, sizeof(ArrowShape) + sizeof(ButtonData));
    ((ArrowShape*) component.customData + sizeof(ButtonData))[0] = {inverted, size};
    return component;
}

void createMainScreenScene() {
    __mainScreenSceneIndex = addScene(create_scene());
}

void registerKeyBindings() {
    Scene* scene = __MAIN_SCREEN_PTR;
    KeyCallback f = [](ButtonState state, uint8_t keyCode) {
        if (state == PRESSED)
            next_focusable_component(__MAIN_SCREEN_PTR);
    };
    KeyCallback f1 = [](ButtonState state, uint8_t keyCode) {
        if (state == PRESSED) {
            Scene* scene = __MAIN_SCREEN_PTR;
            Component* current_component = AS_COMPONENT(get_element(&scene->components, get_focusable_component(scene, scene->tabIndex)));
            if (current_component->type == BUTTON_TYPE) {
                ButtonData* data = getButtonData(current_component);
                data->onClick(current_component);
            }
        }
    };
    KeyCallback f2 = [](ButtonState state, uint8_t keyCode) {
        if (state == PRESSED)
            previous_focusable_component(__MAIN_SCREEN_PTR);
    };
    scene->keyCallbacks[0] = f;
    scene->keyCallbacks[1] = f1;
    scene->keyCallbacks[2] = f2;
}

void initMainScreen() {
    createMainScreenScene();
    registerKeyBindings();
    Component statusBar = createComponent(0, 20, [](Component* context, Arduino_ST7789* display) 
        {drawLine(context->x, context->y, DISPLAY_SIZE, 3, false, WHITE);});
    Component clock = clockWidget({DISPLAY_SIZE - 60, 20 - 16}, {2, WHITE, WHITE, false});
    registerClockWidget(clock.id);
    add_component(__MAIN_SCREEN_PTR, clock);
    add_component(__MAIN_SCREEN_PTR, statusBar);
    add_component(__MAIN_SCREEN_PTR, createArrow({20, (DISPLAY_SIZE >> 1) + 20}, false, 3));
    add_component(__MAIN_SCREEN_PTR, createArrow({DISPLAY_SIZE - 20, (DISPLAY_SIZE >> 1) + 20}, true, 3));
    Scene* scene = __MAIN_SCREEN_PTR;
    highlightComponent(AS_COMPONENT(get_element(&scene->components, get_focusable_component(scene, scene->tabIndex))));
}