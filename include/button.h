#pragma once
#include "component.h"

typedef struct {
    ComponentCallback onClick;
} ButtonData;

Component create_button(Vec2D pos, RendererCallback render, ComponentCallback onClick);
ButtonData* getButtonData(Component* cmp);