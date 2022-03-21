#include "main_screen.h"
#include "Clock.h"
#include "utils.h"
#include "button.h"
#include "application.h"
#include "ui_elements.h"

#define __MAIN_SCREEN_PTR ((Scene*) get_element(&scenes, __mainScreenSceneIndex))

extern List scenes;
static uint8_t __mainScreenSceneIndex;
static uint8_t  indicatorId;

void createMainScreenScene() {
    __mainScreenSceneIndex = addScene(create_scene());
    applications = create_arraylist(1, sizeof(Application));
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
    Component statusBar = createComponent(0, 20, [](Component* context, Arduino_ST7789* display) 
        {drawLine(context->x, context->y, DISPLAY_SIZE, 3, false, WHITE);});
    Component clock = clockWidget({DISPLAY_SIZE - 60, 20 - 16}, {WHITE, WHITE, 2, false});
    registerClockWidget(clock.id);
    add_component(__MAIN_SCREEN_PTR, clock);
    add_component(__MAIN_SCREEN_PTR, statusBar);
    add_component(__MAIN_SCREEN_PTR, create_navigation_button({20, (DISPLAY_SIZE >> 1) + 20}, false, 3, [](Component* ctx) {
        Component* indicator  = findComponentById(indicatorId);
        uint8_t* index = (uint8_t*) get_from_storage(&indicator->customData, 1);
        *index = ((*index) == 0) ? applications.__element_head - 1 : 0;
        indicator->update  = true;
    }));
    Component indicator = create_application_indicator();
    indicatorId = indicator.id;
    add_component(__MAIN_SCREEN_PTR, indicator);
    

    add_component(__MAIN_SCREEN_PTR, create_navigation_button({DISPLAY_SIZE - 20, (DISPLAY_SIZE >> 1) + 20}, true, 3, [](Component* ctx) {
        Component* indicator  = findComponentById(indicatorId);
        uint8_t* index = (uint8_t*) get_from_storage(&indicator->customData, 1);
        *index = ((*index)++ >= applications.__element_head - 1) ? 0 : *index;
        indicator->update = true;
    }));
    highlightComponent(AS_COMPONENT(get_element(&__MAIN_SCREEN_PTR->components, get_focusable_component(__MAIN_SCREEN_PTR, __MAIN_SCREEN_PTR->tabIndex))));
}