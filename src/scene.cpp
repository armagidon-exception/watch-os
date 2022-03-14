#include "scene.h"
#include "stdlib.h"

Scene create_scene() {
    return {
        false, //Show state
        create_arraylist(1, sizeof(Component)), //Components list
        ((KeyCallback*) calloc(3, sizeof(KeyCallback))), //Key callbacks
        0, //Tab index
        create_int_arraylist(1) //Focusable elements
     };
}

void showScene(Scene* scene) {
    scene->show = true;
}
void hideScene(Scene* scene) {
    scene->show = false;
}

void add_component(Scene* scene, Component cmp) {
    if (scene->components.__element_head > scene->components.__initial_capacity - 1) {
        scene->components.array = realloc(scene->components.array, scene->components.__element_size * (scene->components.__element_head + 1));  //Reallocate memory for components array
    }
    AS_COMPONENT(scene->components.array)[scene->components.__element_head++] = cmp;  //Add new component
    if (cmp.focusable) {
        uint8_t index =  (scene->components.__element_head - 1);
        add_int(&scene->focusable_elements, index);
    }
}

uint8_t get_focusable_component(Scene* scene, uint8_t tabIndex) {
    return *((uint8_t*) get_element(&scene->focusable_elements, tabIndex));
}

static void changeComponent(Scene* scene, void (*func)(Scene* scene)) {
    Component* cmp = AS_COMPONENT(get_element(&scene->components, get_focusable_component(scene, scene->tabIndex)));
    dehighlightComponent(cmp);
    func(scene);
    cmp = AS_COMPONENT(get_element(&scene->components, get_focusable_component(scene, scene->tabIndex)));
    highlightComponent(cmp);
}

void next_focusable_component(Scene* scene) {
    changeComponent(scene, [](Scene* scene) {
        if (++scene->tabIndex >= scene->focusable_elements.__element_head)
            scene->tabIndex = 0;
    });
}
void previous_focusable_component(Scene* scene) {
    changeComponent(scene, [](Scene* scene) {
        if (scene->tabIndex == 0)
            scene->tabIndex = scene->focusable_elements.__element_head - 1;
        else
            scene->tabIndex--;
    });
}