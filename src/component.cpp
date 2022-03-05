#include "component.h"

Component createComponent(int x, int y, void (*renderMethod)(Component*, Arduino_ST7789* renderer)) {
    Component cmp;
    cmp.render = renderMethod;
    cmp.update = true;
    cmp.x = x;
    cmp.y = y;
    return cmp;
}