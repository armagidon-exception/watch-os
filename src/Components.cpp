#include "Renderer.h"
#include "Component.h"
#include "math.h"

#define abs(x) ((x) > 0 ? (x) : -(x) )

extern Arduino_ST7789 gDisplay;

Component clock(uint8_t x, uint8_t y, uint8_t scale) {
    gDisplay.fillRect(x, y, 25, 7, WHITE);
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