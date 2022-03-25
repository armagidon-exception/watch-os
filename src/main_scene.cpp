#include "main_screen.h"
#include "Clock.h"
#include "utils.h"
#include "button.h"
#include "application.h"
#include "ui_elements.h"
#include "container.h"

#define MAIN_SCREEN_ID "main_screen"
#define __MAIN_SCREEN_PTR ((Scene*) get_element_by_id(&scenes, MAIN_SCREEN_ID))

extern List scenes;

void createMainScreenScene() {
    auto scene = create_scene(MAIN_SCREEN_ID);
    //Component statusBar = create_container(0, 20);
    Component statusBar = createComponent(0, 20, [](Component* context, Arduino_ST7789* display) {drawLine(context->x, context->y, DISPLAY_SIZE, 3, false, WHITE);});
    Component clock = clockWidget({DISPLAY_SIZE - 60, 20 - 16}, {WHITE, WHITE, 2, false});
    registerClockWidget(clock.id);
    add_component(&scene, clock);
    add_component(&scene, statusBar);
    add_component(&scene, create_navigation_button({20, (DISPLAY_SIZE >> 1) + 20}, false, 3, [](Component* ctx) {change_indicator_index(__MAIN_SCREEN_PTR, 1);}));
    add_component_with_id(&scene, create_application_indicator(), "indicator");
    add_component(&scene, create_navigation_button({DISPLAY_SIZE - 20, (DISPLAY_SIZE >> 1) + 20}, true, 3, [](Component* ctx) {change_indicator_index(__MAIN_SCREEN_PTR, 1);}));

    add_scene(scene);
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
                if (data->onClick == nullptr) return;
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
}