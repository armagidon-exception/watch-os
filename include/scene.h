/**
 * @file scene.h
 * @author your name (you@domain.com)
 * @brief Represents a scene for the OS
 * Holds all the objects that need to be displayed
 * Holds a string id of the scene
 * Holds all key bindings for the scene
 * Holds a component loader for the scene, through which needed components can be added during setup time
 * Holds a tab index to switch focus to a specific component
 * @version 0.1
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "component.h"
#include "List.h"
#include "Keys.h"

#define __CLOCK_SCENE 0
#define __MAINSCREEN_SCENE_INDEX 1

typedef struct Scene{
    bool show:1;
    List components;
    KeyCallback* keyCallbacks;
    uint8_t tabIndex;
    List focusable_elements;
    const char* id;
    void (*component_loader)(Scene* scene);
} Scene;

Scene create_scene(const char* id);
void showScene(Scene* scene);
void hideScene(Scene* scene);
void add_component(Scene* scene, Component cmp);
void add_component_with_id(Scene* scene, Component cmp, const char* id);
uint8_t get_focusable_component(Scene* scene, uint8_t tabIndex);
void next_focusable_component(Scene* scene);
void previous_focusable_component(Scene* scene);