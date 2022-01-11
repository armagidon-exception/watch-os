#include "Component.h"
#include "math.h"

Component createLogo(Bitmap* bitmap, uint8_t w, uint8_t h, uint8_t x, uint8_t y) {
    Texture texture;
    texture.bitmap = *bitmap;

    Component cmp;
    cmp.size = createDimension(w, h);
    cmp.position = createVec2D(x, y);
    cmp.texture = texture;
    cmp.type = LOGO;
    return cmp;
}