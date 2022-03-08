#include <Arduino.h>
#include "Keys.h"
#include "Arduino_ST7789_Fast.h"
#include "Renderer.h"
#include "Clock.h"
#include "main_screen.h"

Arduino_ST7789 gDisplay(7, 8);

void setup() {
  gDisplay.begin();
  gDisplay.clearScreen();
  rendererSetup(&gDisplay);
  initializeClock();
  initClockScene();
  initMainScreen();
  setScene(0);
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

