#include "container.h"

Component create_container(uint8_t x, uint8_t y)  {
    Component cmp = createComponent(x, y, nullptr);
    cmp.focusable = true;
    cmp.type = CONTAINER;
    Container container = {create_arraylist(1, sizeof(Component))};
    put_to_storage(&cmp.customData, &container, sizeof(Container));
    return cmp;
}
void add_child_to_container(Component* container, Component* child)  {
    if (container->type != CONTAINER) return;
    Container* containerData = (Container*) get_from_storage(&container->customData, 0);
    add_element(&containerData->children, child);
}