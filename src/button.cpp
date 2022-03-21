#include "button.h"

Component create_button(Vec2D pos, RendererCallback render, ComponentCallback onClick) {
    Component cmp = createComponent(pos.x, pos.y, render);
    cmp.focusable = true;
    cmp.highlighted = false;
    cmp.type = BUTTON_TYPE;
    put_to_storage(&cmp.customData, &((ButtonData) {onClick}), sizeof(ButtonData));
    return cmp;
}


ButtonData* getButtonData(Component* cmp) {
    if (cmp->type == BUTTON_TYPE)  {
        return (ButtonData*) get_from_storage(&cmp->customData, 0);
    } else return nullptr;
}