#pragma once
#include "utils.h"
#include "Arduino_ST7789_Fast.h"
#define DISPLAY_SIZE 240

void drawLine(int x, int y, int length, uint8_t thickness, bool vertical, uint16_t color);
void rendererSetup(Arduino_ST7789* d);
void render();
void printBitMap(Bitmap* bitmap, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t scale);
void printText(char* text, color color, unit size);