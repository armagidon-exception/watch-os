#include "application.h"

//static const uint8_t SETTINGS_LOGO[] PROGMEM  = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70,0x80, 0x90, 0xA0, 0xB, 0xC0, 0xD0, 0xE0, 0xF0};
static const uint16_t SETTINGS_LOGO[] PROGMEM  = {0, 0, 0xFFFF, 0,
                                                  0, 0, 0xFFFF, 0xFFFF,
                                                  0xFFFF, 0xFFFF, 0, 0,
                                                  0, 0xffff, 0, 0};

static Application create_settings_app() {
    Bitmap map = {SETTINGS_LOGO, sizeof(SETTINGS_LOGO), {4, 4}, 16};
    auto entrypoint = [](Application* context) {
        Serial.println("TEST");
    };
    auto scene = create_scene();
    auto title = "Settings";
    return create_application(title, map, entrypoint);
}

void init_settings_app() {
    registerApplication(&create_settings_app());
}