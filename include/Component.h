#pragma once
#include "Display.h"
#include "utils.h"

typedef enum {
    LOGO
} ComponentType;

typedef union {
    Bitmap bitmap;
    uint16_t background;
} Texture;

typedef struct {
    Vec2D position;
    Dimension size;
    Texture texture;
    bool visible : 1;
    ComponentType type;
} Component;

Component createLogo(Bitmap* bitmap, uint8_t w, uint8_t h, uint8_t x, uint8_t y);
void moveComponent(Component* cmp, Vec2D* delta);