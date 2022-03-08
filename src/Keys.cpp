#include "Keys.h"

void registerKeyHandler(void (*keyhandler)(ButtonState), int key) {
    buttons[key].keyhandler = keyhandler;
}

void dispatch(int key, ButtonState state) {
    buttons[key].state = state;
    (*buttons[key].keyhandler)(state);
}

ButtonState getState(uint8_t key) {
    return buttons[key & 3].state;
}

void tickKeys() {
    for (uint8_t i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
    {
        Button button = buttons[i];
        uint8_t state = digitalRead(button.pin);
        if (state == LOW) {
            if (button.state == PRESSED) {
                dispatch(i, RELEASED);
                button.state = RELEASED;
            }
        } else if (state == HIGH) {
            if (button.state == RELEASED) {
                dispatch(i, PRESSED);
                button.state = PRESSED;
            }
        }
    }   
}

static Button createButton(uint8_t pin, uint8_t id) {
    pinMode(pin, INPUT);
    Button button = {RELEASED, pin & 0xF, nullptr};
    buttons[id & 3] = button;
    return button;
}