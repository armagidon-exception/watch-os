#pragma once
#include "utils.h"
#include "Display.h"

void drawLine(int x, int y, int length, uint8_t thickness, bool vertical, uint16_t color);
void rendererSetup();
void render();
void printBitMap(Bitmap* bitmap, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t scale);