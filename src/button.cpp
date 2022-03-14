#include "button.h"

Component create_button(Vec2D pos, RendererCallback render, ComponentCallback onClick) {
    Component cmp = createComponent(pos.x, pos.y, render);
    cmp.focusable = true;
    cmp.highlighted = false;
    cmp.type = BUTTON_TYPE;
    cmp.customData = calloc(1, sizeof(ButtonData));
    ((ButtonData*) cmp.customData)[0] = {onClick};
    return cmp;
}


ButtonData* getButtonData(Component* cmp) {
    if (cmp->customData != nullptr and cmp->type == BUTTON_TYPE)  {
        return ((ButtonData*) cmp->customData);
    } else return nullptr;
}