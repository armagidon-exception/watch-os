#pragma once
#include "stdbool.h"
#include "stdint.h"

typedef uint16_t color;
typedef const uint16_t* buffer;
typedef uint8_t unit;
typedef int8_t sunit;

typedef struct {
    unit width;
    unit height;
} Dimension;

typedef struct  {
    unit x;
    unit y;
} Vec2D;

typedef struct {
    const uint16_t* colors;
    uint16_t length;
    Dimension size;
    uint8_t scale;
} Bitmap;

void setBit(uint8_t* data, uint8_t bit, bool flag);
Dimension createDimension(unit w, unit h);
Vec2D createVec2D(unit x, unit y);

sunit getVecX(Vec2D* vec);
sunit getVecY(Vec2D* vec);
int arrLen(void* array);