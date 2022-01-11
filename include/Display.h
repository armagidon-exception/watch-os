#pragma once
#include "stdint.h"
#include "utils.h"

#define DISPLAY_SIZE 240
#define RST_PIN 8
#define DC_PIN 7

//Commands
#define ST_SWRESET 0x01
#define ST_SLPOUT 0x11
#define ST_DISPON 0x29
#define ST_COLMOD 0x3A
#define ST_MADCTL 0x36
#define ST_NORON 0x13
#define ST_RASET 0x2B
#define ST_CASET 0x2A
#define ST_RAMWR 0x2C
#define ST_INVON 0x21

#define ST_MADCTL_MY  0x80
#define ST_MADCTL_MX  0x40
#define ST_MADCTL_MV  0x20
#define ST_MADCTL_ML  0x10
#define ST_MADCTL_RGB 0x00

#define BLACK 0x0000
#define WHITE 0xffff

typedef struct {
    uint8_t cursor[2];
    uint8_t drawingArea[4];
    uint16_t __clearColor;
} Display;


void displayInit();

void sendCommand(uint8_t command);
void sendCommandArgument(uint8_t argument);
void sendSingularData(uint16_t data);
void sendRepeatedData(uint16_t data, uint16_t quantity);

void displaySetDrawingArea(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
uint8_t drawingAreaWidth();
uint8_t drawingAreaHeight();
void clearScreen();
void fillArea(Vec2D* pos, Dimension* size, color color);
void fillScreen(uint16_t color);
void printBufScaled(buffer buf, Dimension* size, const uint8_t scaleFactor);
void printBufScaledWithClearDeltas(buffer buf, Dimension* size, const unit scaleFactor, Vec2D* delta);