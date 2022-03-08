#pragma once
#include "component.h"
#include "List.h"

typedef struct {
    bool show:1;
    List components;
} Scene;

Scene create_scene();
void showScene(Scene* scene);
void hideScene(Scene* scene);
void add_component(Scene* scene, Component cmp);