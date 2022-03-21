#pragma once
#include "component.h"
#include "button.h"
#include "Arduino_ST7789_Fast.h"
#include "stdlib.h"

typedef struct ArrowShape {
    bool inverted;
    uint8_t size;
} ArrowShape;

static Component create_navigation_button(Vec2D pos, bool inverted, uint8_t size, void (*onClick)(Component*)) {
    Component component = create_button(pos, [](Component* context, Arduino_ST7789* display){
        ArrowShape* shape = (ArrowShape*) get_from_storage(&context->customData, 1);
        //Verticies
        uint8_t x1 = context->x, x2 = context->x + (shape->inverted ? -10: 10) * shape->size, x3 = context->x + (shape->inverted ? -10 : 10) * shape->size;
        uint8_t y1 = context->y, y2 = context->y + 10 * shape->size, y3 = context->y - 10 * shape->size;
        uint8_t rxmin = min(x1, x2),
                    rymin = min(y1, min(y2, y3)),
                    rxmax = max(x1, x2),
                    rymax = max(y1, max(y2, y3));
        if (!context->highlighted) {
            display->fillRect(rxmin, rymin, rxmax - rxmin, rymax - rymin, BLACK);
            display->fillTriangle(x1, y1, x2, y2, x3, y3, WHITE);
        } else {
            display->fillRect(rxmin, rymin, rxmax - rxmin, rymax - rymin, WHITE);
            display->fillTriangle(x1, y1, x2, y2, x3, y3, BLACK);
        }
    }, onClick);
    put_to_storage(&component.customData, &((ArrowShape) {inverted, size}), sizeof(ArrowShape));
    return component;
}

static Component create_application_indicator() {
    Component cmp = create_button({120, 120 + 20}, [](Component* context, Arduino_ST7789* display) {
        uint8_t applicationIndex = *(uint8_t*) get_from_storage(&context->customData, 1);
        Application* app = (Application*) get_element(&applications, applicationIndex);
        if (app == nullptr) {
            display->fillRect(context->x, context->y, 20, 20, WHITE);
            return;
        }
        bool inv = context->highlighted ? true : false;
        display->drawBufferScaled(app->icon.colors, context->x - app->icon.size.width * app->icon.scale / 2, context->y - app->icon.size.height * app->icon.scale / 2, app->icon.size.width, app->icon.size.height, app->icon.scale, inv);

        const uint8_t tw = strlen(app->title) * 6 * 2, th = 8 * 2;
        display->fillRect(0, context->y - th / 2 + 50, DISPLAY_SIZE, th, BLACK);
        display->setCursor(context->x - tw / 2, context->y - th  / 2 + 50);
        display->setTextSize(2);
        display->setTextColor(WHITE);
        display->setTextWrap(false);
        display->println(app->title);

    }, [](Component* context) {
        uint8_t applicationIndex = *(uint8_t*) get_from_storage(&context->customData, 1);
        Application* app = (Application*) get_element(&applications, applicationIndex);
        if  (app == nullptr) return;
        app->invoke(app);
    });
    uint8_t applicationIndex = 0;
    put_to_storage(&cmp.customData, &applicationIndex, sizeof(uint8_t));
    return cmp;
}