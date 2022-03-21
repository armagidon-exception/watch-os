#include "application.h"

static const uint16_t SETTINGS_LOGO[] PROGMEM  = {0xffff, 0, 0, 0xffff,
                                                  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
                                                  0, 0xFFFF, 0, 0xFFFF,
                                                  0xffff, 0xffff, 0xffff, 0xffff};

Application create_calc_application() {
Bitmap map = {SETTINGS_LOGO, sizeof(SETTINGS_LOGO), {4, 4}, 16};
    auto entrypoint = [](Application* context) {
        Serial.println("TEST");
    };
    auto scene = create_scene();
    auto title = "Calculator";
    return create_application(title, map, entrypoint);
}

void init_calc_app() {
    registerApplication(&create_calc_application());
}