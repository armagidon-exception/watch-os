#pragma once
#include "component.h"

typedef struct {
    uint8_t __component_index;
    bool show:1;
    Component* components;
} Scene;

Scene createScene();
void showScene(Scene* scene);
void hideScene(Scene* scene);
void addComponent(Scene* scene, Component cmp);