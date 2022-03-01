#include <Arduino.h>
#include "Keys.h"
#include "Arduino_ST7789_Fast.h"
#include "Renderer.h"
#include "Clock.h"

Arduino_ST7789 gDisplay(7, 8);

void setup() {
  //displayInit();
  gDisplay.begin();
  gDisplay.clearScreen();
  rendererSetup(&gDisplay);
  initializeClock();
}

static u32 timer = millis();
void loop() {
  tickKeys();
  tickClock();
  if (millis() - timer >= 16) {
    timer = millis();
    //Rendering
    render();
  }
}

