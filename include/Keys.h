//KeyboardAPI
#pragma once
#include "utils.h"
#include "Arduino.h"

#define FIRST_KEY 0
#define SECOND_KEY 1
#define FIRST_PIN 4
#define SECOND_PIN 5

typedef enum {
    PRESSED,
    RELEASED
} ButtonState;

typedef struct {
    ButtonState state;
    uint8_t pin:4;
    void (*keyhandler)(ButtonState);
} Button;

Button createButton(uint8_t pin, uint8_t id);

static Button buttons[] = {createButton(FIRST_PIN, FIRST_KEY), createButton(SECOND_PIN, SECOND_KEY)};

void registerKeyHandler(void (*keyhandler)(ButtonState), int key);
void dispatch(int key, ButtonState state);
void tickKeys();
ButtonState getState(uint8_t key);