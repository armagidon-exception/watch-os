#include "utils.h"

void setBit(uint8_t* data, uint8_t bit, bool flag) {
    if (flag) {
        *data = *data | (1 << bit);
    } else {
        *data = *data & ~(1 << bit);
    }
}

Bitmap createBitmap(uint16_t* bitmap, uint16_t size) {
    return {bitmap, size};
}

Dimension createDimension(unit w, unit h) {
    return {w, h};
}

Vec2D createVec2D(unit x, unit y) {
    return {x, y};
}

sunit getVecX(Vec2D* vec) {
    return (sunit) vec->x;
}
sunit getVecY(Vec2D* vec) {
    return (sunit) vec->y;
}

unit abs(sunit x) {
    if (x & (1 << 7) != 0) {
        x = ~x;
        x + 1;
    }
    return x;
}