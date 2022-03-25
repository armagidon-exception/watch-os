#include <Arduino.h>
#include "Keys.h"
#include "SPI.h"
#include "Arduino_ST7789_Fast.h"
#include "Renderer.h"
#include "Clock.h"
#include "main_screen.h"

Arduino_ST7789 gDisplay(7, 8);

extern void init_settings_app();
extern void init_calc_app();

void setup() {
  Serial.begin(9600);
  gDisplay.begin();
  gDisplay.clearScreen();
  rendererSetup(&gDisplay);
  initializeClock();
  initClockScene();
  initMainScreen();
  init_settings_app();
  init_calc_app();
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

