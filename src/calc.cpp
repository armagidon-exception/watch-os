#include "application.h"
#include "Renderer.h"
#include "ui_elements.h"

static const uint16_t SETTINGS_LOGO[] PROGMEM  = {0xffff, 0, 0, 0xffff,
                                                  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
                                                  0, 0xFFFF, 0, 0xFFFF,
                                                  0xffff, 0xffff, 0xffff, 0xffff};

static uint8_t offsetIndex = 0;
static const char button_labels[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '*', '/', '='};
static int16_t currentNumber = 0;

static void cmp_ldr(Scene* s) {
    auto numberCallback = [](Component* ctx) {
        NumberLabel* label = (NumberLabel*) get_from_storage(&ctx->customData, 1);
        currentNumber = currentNumber * 10 + label->number;
        Component* input_label = (Component*) get_element_by_id(&get_current_scene()->components, "input_label");
        Label* l = (Label*) get_from_storage(&input_label->customData, 0);
        sprintf(l->label, "%d", currentNumber);
        input_label->update = true;
    };
    {
        Component cmp = create_label(0, 40, 5, "        ");
        cmp.highlighted = true;
        add_component_with_id(s, cmp, "input_label");
        offsetIndex++;
    }
    {
        uint8_t row_size = 0;
        uint8_t yoff = 0;
        for (uint8_t i = 0; i < sizeof(button_labels); i++) {
            if (6 * 5 * (i - row_size) >= DISPLAY_SIZE) {
                yoff += 40;
                row_size = i;
            }
            Component cmp; 
            uint8_t x = (uint8_t) (30 * (i - row_size)), y = (uint8_t) (100 + yoff);
            if (i < 10) {
                cmp = create_number_label_button({x, y}, {5, i}, numberCallback);
            }
            else {
                char* l = (char*) calloc(2, sizeof(char));
                l[0] = button_labels[i];
                l[1] = '\0';
                cmp = create_label_button({x, y}, {l, 5}, nullptr);
            }
            add_component(s, cmp);
        }
    }
}

static void init_calc_scene(Scene* scene) {
    scene->component_loader = cmp_ldr;
    KeyCallback f = [](ButtonState state, uint8_t keyCode) {
        if (state == PRESSED)
            next_focusable_component(get_current_scene());
    };
    KeyCallback f1 = [](ButtonState state, uint8_t keyCode) {
        if (state == PRESSED) {
            Scene* scene = get_current_scene();
            Component* current_component = AS_COMPONENT(get_element(&scene->components, get_focusable_component(scene, scene->tabIndex)));
            if (current_component->type == BUTTON_TYPE) {
                ButtonData* data = getButtonData(current_component);
                if (data->onClick == nullptr) return;
                data->onClick(current_component);
            }
        }
    };
    KeyCallback f2 = [](ButtonState state, uint8_t keyCode) {
        if (state == PRESSED)
            previous_focusable_component(get_current_scene());
    };
    scene->keyCallbacks[0] = f;
    scene->keyCallbacks[1] = f1;
    scene->keyCallbacks[2] = f2;
}

Application create_calc_application() {
    Bitmap map = {SETTINGS_LOGO, sizeof(SETTINGS_LOGO), {4, 4}, 16};
    auto entrypoint = [](Application* context) {
        setScene(find_scene_index_by_id(context->scene.id));
        Component* highlighted = (Component*) get_element(&context->scene.components, get_focusable_component(&context->scene, context->scene.tabIndex));
        dehighlightComponent(highlighted);
        offsetIndex = 0;
    };
    auto title = "Calculator";
    Application application = create_application(title, map, entrypoint);
    init_calc_scene(&application.scene);
    add_scene(application.scene);
    return application;
}

void init_calc_app() {
    Application app = create_calc_application();
    registerApplication(&app);
}