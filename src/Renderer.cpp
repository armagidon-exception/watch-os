#include "Renderer.h"
#include "utils.h"
#include <Arduino.h>

#define BITMAP_SCANSIZE 2
#define SCALE_FACTOR 120

static Component logo;
extern Display display;
static const uint16_t bitmap[] PROGMEM = {
    0xF30A, 0x5711,
    0x651D, 0xE521
};

void rendererSetup() {
    Serial.begin(9600);
    clearScreen();
    logo = createLogo(&createBitmap(bitmap, sizeof(bitmap) / sizeof(bitmap[0])), 64, 64, 0, 0);
    logo.visible = true;
    pinMode(4, INPUT);
    pinMode(5, INPUT);
}

static Vec2D direction = createVec2D(0, 0);
void render() {
    direction.x = 0;
    if (digitalRead(4) == HIGH) {
        direction.x = -2;
    } else if (digitalRead(5) == HIGH) {
        direction.x = 2;
    }
    moveComponent(&logo, &direction);
    // if (logo.position.x + logo.size.width >= DISPLAY_SIZE) 
    //     direction.x = -2;
    // else if (logo.position.x == 0) 
    //     direction.x = 2;
    // if (logo.position.y + logo.size.height >= DISPLAY_SIZE) 
    //     direction.y = -2;
    // else if (logo.position.y == 0) 
    //     direction.y = 2;
}

void drawLine(int x, int y, int length, uint8_t thickness, bool vertical, uint16_t color) {
    fillArea(&createVec2D(x, y), &createDimension(vertical ? thickness : length, vertical ? length : thickness), color);
}

void renderStatusBar() {
    drawLine(0, 20, DISPLAY_SIZE, 2, false, WHITE);
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
    const int8_t dx = delta->x, dy = delta->y;
    if (cmp->type == LOGO) {
        const unit scaleFactor = sqrt( ((uint16_t) (cmp->size.width * cmp->size.height)) / cmp->texture.bitmap.size);
        const unit aw = cmp->size.width / scaleFactor;
        const unit ah = cmp->size.height / scaleFactor;

        //Let x = 0
        if (cmp->position.x >= DISPLAY_SIZE || cmp->position.y >= DISPLAY_SIZE) return;
        unit x = cmp->position.x, y = cmp->position.y, w = cmp->size.width, h = cmp->size.height;
        if (dx > 0) {
            w += dx;
        } else {
            x += dx;
            w -= dx;
        }
        if (dy > 0) {
            h += dy;
        } else {
            y += dy;
            h -= dy;
        }
        //fillArea(&createVec2D(x, y), &createDimension(w, h), WHITE);
        displaySetDrawingArea(x, y, w, h);
        printBufScaledWithClearDeltas(cmp->texture.bitmap.bitmap, &createDimension(aw, ah), scaleFactor, delta);
        cmp->position.x += dx;
        cmp->position.y += dy;
    }
}