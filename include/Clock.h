#pragma once
#include "Renderer.h"
#include "utils.h"

typedef struct {
    uint8_t size;
    uint16_t bg;
    uint16_t fg;
    bool fill:1;
} ClockShape;

Component clockWidget(uint8_t size, uint16_t bg, uint16_t fg, bool fill);
Component clockWidget(Vec2D position, ClockShape shape);
Component clockWidget(ClockShape shape);

void tickClock();
void initializeClock();
void initClockScene();
void registerClockWidget(uint8_t clockWidget);