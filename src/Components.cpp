#include "Renderer.h"
#include "Component.h"
#include "math.h"

#define abs(x) ((x) > 0 ? (x) : -(x) )

extern Arduino_ST7789 gDisplay;

Component createLogo(Bitmap* bitmap, uint8_t w, uint8_t h, uint8_t x, uint8_t y) {
    Texture texture;
    texture.bitmap = *bitmap;

    Component cmp;
    cmp.size = createDimension(w, h);
    cmp.position = createVec2D(x, y);
    cmp.prevPos = createVec2D(x, y);
    cmp.texture = texture;
    cmp.type = LOGO;
    return cmp;
}

void printBitMap(Bitmap* bitmap, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t scale) {
    if (x >= DISPLAY_SIZE || y >= DISPLAY_SIZE) return;
    if (scale == 0) 
        scale = 1;
    for (size_t y = 0; y < h; y++)
    {
        for (size_t x = 0; x < w; x++)
        {
            gDisplay.fillRect(x * scale, y * scale, scale, scale, pgm_read_word(&bitmap->bitmap[x + y * w]));
        }
        
    }
    
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