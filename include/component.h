#pragma once
#include "utils.h"
#include "custom_data_storage.h"
#include "Arduino_ST7789_Fast.h"

#define AS_COMPONENT(a) ((Component*) a)

//Types

#define ICON_TYPE 0
#define BUTTON_TYPE 1
#define CONTAINER 2
#define CUSTOM 3

struct Component {
    uint8_t x;
    uint8_t y;
    void (*render)(Component*, Arduino_ST7789*);
    bool update;
    uint8_t id;
    DataStorage customData;
    bool highlighted;
    bool focusable;
    uint8_t type;
};

typedef void (*RendererCallback)(Component*, Arduino_ST7789*);
typedef void (*ComponentCallback)(Component*);


Component createComponent(int x, int y, RendererCallback render);
void highlightComponent(Component* cmp);
void dehighlightComponent(Component* cmp);