#include <Arduino.h>
#include "Renderer.h"
#include "Keys.h"



void setup() {
  displayInit();
  rendererSetup();
}

static u32 timer = millis();
void loop() {
  if (millis() - timer >= 16) {
    timer = millis();
    //Rendering
    tickKeys();
    render();
  }
}

