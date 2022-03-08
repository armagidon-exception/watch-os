#include "scene.h"
#include "stdlib.h"

Scene create_scene() {
    return {false, create_arraylist(1, sizeof(Component))};
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
    ((Component*) scene->components.array)[scene->components.__element_head++] = cmp; //Add new component
}