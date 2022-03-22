#pragma once
#include "component.h"
#include "List.h"
#include "Keys.h"

#define __CLOCK_SCENE 0
#define __MAINSCREEN_SCENE_INDEX 1

typedef struct {
    bool show:1;
    List components;
    KeyCallback* keyCallbacks;
    uint8_t tabIndex;
    List focusable_elements;
    const char* id;
} Scene;

Scene create_scene(const char* id);
void showScene(Scene* scene);
void hideScene(Scene* scene);
void add_component(Scene* scene, Component cmp);
uint8_t get_focusable_component(Scene* scene, uint8_t tabIndex);
void next_focusable_component(Scene* scene);
void previous_focusable_component(Scene* scene);