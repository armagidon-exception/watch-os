#pragma once
#include "utils.h"
#include "Arduino_ST7789_Fast.h"

typedef union {
    Bitmap bitmap;
    uint16_t background;
} Texture;

// typedef union
// {
//     struct {
//         Vec2D position;
//         Vec2D prevPos;
//         Dimension size;
//         Texture texture;
//         bool visible : 1;
//     };
//     void (*render)();
// } Component;

typedef struct {
    void (*render)(Arduino_ST7789*);
    bool updated:1;
} Component;