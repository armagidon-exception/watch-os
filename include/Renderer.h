#pragma once
#include "utils.h"
#include "Arduino_ST7789_Fast.h"
#define DISPLAY_SIZE 240

void drawLine(int x, int y, int length, uint8_t thickness, bool vertical, uint16_t color);
void rendererSetup(Arduino_ST7789* d);
void render();