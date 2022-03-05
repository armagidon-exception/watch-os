#include "scene.h"

Scene createScene() {
    Scene scene;
    scene.show = false;
    scene.__component_index  = 0;
    scene.components = (Component*) malloc(sizeof(Component));
    return scene;
}

void showScene(Scene* scene) {
    scene->show = true;
}
void hideScene(Scene* scene) {
    scene->show =  false;
}

void addComponent(Scene* scene, Component cmp) {
    if (scene->__component_index > 0) {
        realloc(scene->components, sizeof(Component) * (scene->__component_index + 2));  //Reallocate memory for components array
    }
    scene->components[scene->__component_index++] = cmp; //Add new component
}