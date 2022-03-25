#include "application.h"
#include "Renderer.h"
#include "ui_elements.h"
#include "stdlib.h"
#include "Clock.h"

//static const uint8_t SETTINGS_LOGO[] PROGMEM  = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70,0x80, 0x90, 0xA0, 0xB, 0xC0, 0xD0, 0xE0, 0xF0};
static const uint16_t SETTINGS_LOGO[] PROGMEM  = {0, 0, 0xFFFF, 0,
                                                  0, 0, 0xFFFF, 0xFFFF,
                                                  0xFFFF, 0xFFFF, 0, 0,
                                                  0, 0xffff, 0, 0};

static uint8_t tmpHours = get_hours();
static uint8_t tmpMinutes = get_minutes();
static bool pinned = false;
static uint8_t pinned_cmp = 0;

static const uint8_t hours_id = 0;
static const uint8_t minutes_id = 1;

static void init_settings_scene(Scene* s) {
    Component timeLabel = create_label(10, 10, 3, "Time: >");
    add_component(s, timeLabel);
    {
        char* hoursString = (char*) calloc(3, sizeof(char));
        sprintf(hoursString, "%02d", tmpHours);
        Component hoursLabel = create_label(120, 10, 3, hoursString);
        hoursLabel.focusable = true;
        uint8_t tmph = hours_id;
        put_to_storage(&hoursLabel.customData, &tmph, sizeof(uint8_t));
        add_component_with_id(s, hoursLabel, "hours");
    }
    {
        char* minutesString = (char*) calloc(3, sizeof(char));
        Component minutesLabel = create_label(160, 10, 3, minutesString);
        sprintf(minutesString, "%02d", tmpMinutes);
        minutesLabel.focusable = true;
        uint8_t tmpm = minutes_id;
        put_to_storage(&minutesLabel.customData, &tmpm, sizeof(uint8_t));
        add_component_with_id(s, minutesLabel, "minutes");
    }
    {
        Component saveButton = create_button({120, 200}, [](Component* context, Arduino_ST7789* renderer) {
            if (!context->highlighted)
                printText(renderer, context->x, context->y, 4, WHITE, BLACK, "SAVE");
            else
                printText(renderer, context->x, context->y, 4, BLACK, WHITE, "SAVE");
        }, [](Component* context) {
            set_minutes(tmpMinutes);
            set_hours(tmpHours);
            setScene(1);
        });
        add_component(s, saveButton);
    }
    {
        Component exitButton = create_button({0, 200}, [](Component* context, Arduino_ST7789* renderer) {
            if (!context->highlighted)
                printText(renderer, context->x, context->y, 4, WHITE, BLACK, "EXIT");
            else
                printText(renderer, context->x, context->y, 4, BLACK, WHITE, "EXIT");
        }, [](Component* context) {
            setScene(1);
        });
        add_component(s, exitButton);
    }

    KeyCallback f = [](ButtonState state, uint8_t keyCode) {
        Scene* s = &((Application*) (get_element_by_id(&applications, "Settings")))->scene;
        if (state == PRESSED) {
            Serial.println(pinned);
            if (!pinned)
                next_focusable_component(s);
            else {
                Component* cmp = findComponentById(pinned_cmp);
                uint8_t* i = (uint8_t*) get_from_storage(&cmp->customData, 1);
                if (i != nullptr) {
                    Label* label = (Label*) get_from_storage(&cmp->customData, 0);
                    if (*i == hours_id) {
                        CHANGE_INDEX(1, 23, &tmpHours);
                        sprintf(label->label, "%02d", tmpHours);
                    }
                    else if (*i == minutes_id) {
                        CHANGE_INDEX(1, 59, &tmpMinutes);
                        sprintf(label->label, "%02d", tmpMinutes);
                    }
                    cmp->update = true;   
                }
            }
        }
    };
    KeyCallback f1 = [](ButtonState state, uint8_t keyCode) {
        if (state == PRESSED) {
            Scene* s = &((Application*) (get_element_by_id(&applications, "Settings")))->scene;
            Component* current_component = (Component*) (get_element(&s->components, get_focusable_component(s, s->tabIndex)));
            if (current_component->type == BUTTON_TYPE) {
                ButtonData* data = getButtonData(current_component);
                if (data->onClick == nullptr) return;
                data->onClick(current_component);
            } else if (current_component->type == LABEL_TYPE) {
                if (!pinned) {
                    pinned = true;
                    pinned_cmp = current_component->id;
                } else
                    pinned = false;
            }
        }
    };
    KeyCallback f2 = [](ButtonState state, uint8_t keyCode) {
        Scene* s = &((Application*) (get_element_by_id(&applications, "Settings")))->scene;
        if (state == PRESSED) {
            Serial.println(pinned);
            if (!pinned)
                previous_focusable_component(s);
            else {
                Component* cmp = findComponentById(pinned_cmp);
                uint8_t* i = (uint8_t*) get_from_storage(&cmp->customData, 1);
                if (i != nullptr) {
                    Label* label = (Label*) get_from_storage(&cmp->customData, 0);
                    if (*i == hours_id) {
                        CHANGE_INDEX(-1, 23, &tmpHours);
                        sprintf(label->label, "%02d", tmpHours);
                    }
                    else if (*i == minutes_id) {
                        CHANGE_INDEX(-1, 59, &tmpMinutes);
                        sprintf(label->label, "%02d", tmpMinutes);
                    }
                    cmp->update = true;   
                }
            }
        }   
    };
    s->keyCallbacks[0] = f;
    s->keyCallbacks[1] = f1;
    s->keyCallbacks[2] = f2;

}

static Application create_settings_app() {
    Bitmap map = {SETTINGS_LOGO, sizeof(SETTINGS_LOGO), {4, 4}, 16};
    auto entrypoint = [](Application* context) {
        init_settings_scene(&context->scene);
        add_scene(context->scene);
        setScene(find_scene_index_by_id(context->scene.id));
    };
    auto title = "Settings";
    return create_application(title, map, entrypoint);
}

void init_settings_app() {
    Application app = create_settings_app();
    registerApplication(&app);
}