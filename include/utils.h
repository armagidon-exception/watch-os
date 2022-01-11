#pragma once
#include "stdbool.h"
#include "stdint.h"

typedef uint16_t color;
typedef const uint16_t* buffer;
typedef uint8_t unit;

typedef struct {
    buffer bitmap;
    uint16_t size;
} Bitmap;

typedef struct {
    unit width;
    unit height;
} Dimension;

typedef struct  {
    unit x;
    unit y;
} Vec2D;

void setBit(uint8_t* data, uint8_t bit, bool flag);
Bitmap createBitmap(const uint16_t* bitmap, uint16_t size);
Dimension createDimension(unit w, unit h);
Vec2D createVec2D(unit x, unit y);