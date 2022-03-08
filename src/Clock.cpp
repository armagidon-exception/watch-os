#include "Clock.h"
#include "Renderer.h"
#include "scene.h"
#define CLOCK_SCALE 6
#define CLOCK_X DISPLAY_SIZE / 2 - 15 * CLOCK_SCALE
#define CLOCK_Y DISPLAY_SIZE / 2 - 8 * CLOCK_SCALE
#define __CLOCK_PTR ((Scene*) get_element(&scenes, __clockSceneIndex))

static volatile uint8_t seconds = 0;
static volatile uint8_t minutes = 0;
static volatile uint8_t hours = 0;
static uint8_t __clockSceneIndex;

static unsigned long timeStump = millis();
extern List scenes;
static List clockWidgetIds;

typedef struct {
    uint8_t size; uint16_t bg; uint16_t fg; bool fill:1;
} ClockShape;

void tickClock() {
    bool update = false;
    if (millis() - timeStump >= 1000) {
        seconds++;
        timeStump = millis();
    }
    if (seconds >= 60) {
        update = true;
        seconds = 0;
        minutes++;
    }
    if (minutes >= 60) {
        hours++;
        minutes=0;
        update = true;
    }
    if (update) {
        for_each(&clockWidgetIds, [](void* element) {
            uint8_t* id = (uint8_t*) element;
            Component* widget = findComponentById(*id);
            widget->update = true;
        });
    }
}

void renderClock(Component* context, Arduino_ST7789* display) {
    ClockShape shape = ((ClockShape*) context->customData)[0];
    if (shape.fill) {
        display->fillRect(context->x, context->y, 30 * shape.size, 8 * shape.size, shape.bg);
    } else {
        display->fillRect(context->x, context->y, 30 * shape.size, 8 * shape.size, BLACK);
        display->drawRect(context->x, context->y, 30 * shape.size, 8 * shape.size, shape.bg);
    }
    display->setCursor(context->x, context->y);
    display->setTextSize(shape.size);
    display->setTextColor(shape.fg);
    display->setTextWrap(false);
    char s[6];
    sprintf(s, "%02d:%02d", hours, minutes);
    display->print(s);
}


void registerClockWidget(uint8_t clockWidget) {
    add_int(&clockWidgetIds, clockWidget);
}

void initializeClock() {
    clockWidgetIds = create_int_arraylist(1);
}

void initClockScene() {
    __clockSceneIndex = addScene(create_scene());
    Component clock = clockWidget(CLOCK_SCALE, WHITE, BLACK, true);
    clock.x = CLOCK_X;
    clock.y = CLOCK_Y;
    add_component(__CLOCK_PTR, clock);
    registerClockWidget(clock.id);
}

Component clockWidget(uint8_t size, uint16_t bg, uint16_t fg, bool fill) {
    Component component = createComponent(0, 0, renderClock);
    component.customData = calloc(1, sizeof(ClockShape));
    ClockShape shape = {size, bg, fg, fill};
    ((ClockShape*) component.customData)[0] = shape;
    return (component);
}