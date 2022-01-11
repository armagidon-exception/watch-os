#include "Renderer.h"
#include "Component.h"
#include "math.h"
#define abs(x) ((x)>0?(x):-(x))

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

void printBitMap(Bitmap* bitmap, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t scale) {
    if (x >= DISPLAY_SIZE || y >= DISPLAY_SIZE) return;
    if (scale == 0) 
        scale = 1;
    displaySetDrawingArea(x, y, w * scale, h * scale);
    printBufScaled(bitmap->bitmap, &createDimension(w, h), scale);
}

void renderComponent(Component* cmp) {
    if (!cmp->visible) return;
    if (cmp->type == LOGO) {
        const uint8_t scaleFactor = sqrt( ((uint16_t) (cmp->size.width * cmp->size.height)) / cmp->texture.bitmap.size);
        const uint8_t aw = cmp->size.width / scaleFactor;
        const uint8_t ah = cmp->size.height / scaleFactor;

        printBitMap(&cmp->texture.bitmap, cmp->position.x, cmp->position.y, aw, ah, scaleFactor);
    }
}

void moveComponent(Component* cmp, Vec2D* delta) {
    if (delta->x == 0 && delta->y == 0) return;
    if (!cmp->visible) return;
    const sunit dx = delta->x, dy = delta->y;
    if (cmp->type == LOGO) {
        const unit scaleFactor = sqrt( ((uint16_t) (cmp->size.width * cmp->size.height)) / cmp->texture.bitmap.size);
        const unit aw = cmp->size.width / scaleFactor;
        const unit ah = cmp->size.height / scaleFactor;
        //Let x = 0
        if (cmp->position.x + dx >= DISPLAY_SIZE || cmp->position.y + dy >= DISPLAY_SIZE) return;
        cmp->position.x += dx;
        cmp->position.y += dy;
        unit x = cmp->position.x, y = cmp->position.y, w = cmp->size.width, h = cmp->size.height;
        
        displaySetDrawingArea(x - (dx > 0 ? dx : 0), y, w, h);
        printBufScaledWithClearDeltas(cmp->texture.bitmap.bitmap, &createDimension(aw, ah), scaleFactor, delta);
    }
}