#pragma once
#include "Arduino_ST7789_Fast.h"

typedef struct Component{
    uint8_t x;
    uint8_t y;
    void (*render)(Component*, Arduino_ST7789*);
    bool update;
    uint8_t id;
    void* customData;
} Component;

Component createComponent(int x, int y, void (*render)(Component*, Arduino_ST7789*));