//KeyboardAPI
#pragma once
#include "utils.h"
#include "Arduino.h"

#define FIRST_KEY 0
#define SECOND_KEY 1
#define THIRD_KEY 2

#define FIRST_PIN 4
#define SECOND_PIN 5
#define THIRD_PIN 6

typedef enum {
    PRESSED,
    RELEASED
} ButtonState;

typedef void (*KeyCallback)(ButtonState, uint8_t);

typedef struct {
    ButtonState state;
    uint8_t pin:4;
    KeyCallback keyhandler;
} Button;

Button createButton(uint8_t pin, uint8_t id);

static Button buttons[] = {createButton(FIRST_PIN, FIRST_KEY), createButton(SECOND_PIN, SECOND_KEY), createButton(THIRD_PIN, THIRD_KEY)};

void registerKeyHandler(KeyCallback, int key);
void dispatch(int key, ButtonState state);
void tickKeys();
ButtonState getState(uint8_t key);