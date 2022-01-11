#include <Arduino.h>
#include "Renderer.h"


void setup() {
  displayInit();
  rendererSetup();
}

static u32 timer = millis();
void loop() {
  if (millis() - timer >= 16) {
    timer = millis();
    //Rendering
    render();
  }
}