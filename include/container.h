#pragma once
#include "component.h"
#include "List.h"

typedef struct {
    List children;
    uint8_t tab_index;
} Container;

Component create_container(uint8_t, uint8_t);
void add_child_to_container(Component*, Component*);