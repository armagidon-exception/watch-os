#pragma once
#include "Renderer.h"

Component clockWidget(uint8_t size, uint16_t bg, uint16_t fg, bool fill);

void tickClock();
void initializeClock();
void initClockScene();
void registerClockWidget(uint8_t clockWidget);