#include "Arduino.h"
#include "SPI.h"

#define DISPLAY_DEFINITION

#include "Display.h"
#include "utils.h"

extern Display display;

void displaySetDrawingAreaAbsolute(uint8_t x, uint8_t y, uint8_t ex, uint8_t ey) {
    display.drawingArea[0] = x >= DISPLAY_SIZE ? x - DISPLAY_SIZE : x; //startX
    display.drawingArea[1] = y >= DISPLAY_SIZE ? y - DISPLAY_SIZE : y; //startY
    display.drawingArea[2] = ex >= DISPLAY_SIZE ? DISPLAY_SIZE - 1 : ex; //endX
    display.drawingArea[3] = ey >= DISPLAY_SIZE ? DISPLAY_SIZE - 1 : ey; //endY

    sendCommand(ST_CASET);
    sendSingularData(display.drawingArea[0]);
    sendSingularData(display.drawingArea[2]);
    sendCommand(ST_RASET);
    sendSingularData(display.drawingArea[1]);
    sendSingularData(display.drawingArea[3]);
}

void displaySetDrawingArea(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    display.drawingArea[0] = x >= DISPLAY_SIZE ? x - DISPLAY_SIZE : x; //startX
    display.drawingArea[1] = y >= DISPLAY_SIZE ? y - DISPLAY_SIZE : y; //startY
    display.drawingArea[2] = x + (w + x >= DISPLAY_SIZE ? DISPLAY_SIZE - x : w) - 1; //endX
    display.drawingArea[3] = y + (h + y >= DISPLAY_SIZE ? DISPLAY_SIZE - y : h) - 1; //endY

    sendCommand(ST_CASET);
    sendSingularData(display.drawingArea[0]);
    sendSingularData(display.drawingArea[2]);
    sendCommand(ST_RASET);
    sendSingularData(display.drawingArea[1]);
    sendSingularData(display.drawingArea[3]);
}

void fillArea(Vec2D* pos, Dimension* size, color color) {
    displaySetDrawingArea(pos->x, pos->y, size->width, size->height);
    sendCommand(ST_RAMWR);
    const uint8_t nw = drawingAreaWidth();
    const uint8_t nh = drawingAreaHeight();
    sendRepeatedData(color, nw * nh);
}

void clearScreen() {
    fillArea(&createVec2D(0, 0), &createDimension(DISPLAY_SIZE, DISPLAY_SIZE), display.__clearColor);
}

void fillScreen(uint16_t color) {
    fillArea(&createVec2D(0, 0), &createDimension(DISPLAY_SIZE, DISPLAY_SIZE), color);
}