#include "List.h"

List create_arraylist(uint8_t __initial_capacity, uint8_t __element_size) {
    if (__initial_capacity == 0) 
        __initial_capacity = 1;
    return {calloc(__initial_capacity, __element_size), 0, __element_size, __initial_capacity};
}

List create_int_arraylist(uint8_t __initial_capacity) {
    return create_arraylist(__initial_capacity, sizeof(uint8_t));
}

void *get_element(List* list, uint8_t index) {
    return (list->array + (index * list->__element_size));
}

//Iterate through all elements of the copy of the list
void for_each_copied(List list, void (*action)(void* context)) {
    for_each(&list, action);
}

void for_each(List* list, void (*action)(void* context)) {
    for (uint8_t i = 0; i < list->__element_head; i++)
    {
        action(get_element(list, i));
    }
}

void deleteList(List* list) {
    free(list->array);
}

void add_int(List* list, uint8_t element) {
    if (list->__element_head > list->__initial_capacity - 1) {
        list->array = realloc(list->array, list->__element_size * (list->__element_head + 1));  //Reallocate memory for components array
    }
    ((uint8_t*) list->array)[list->__element_head++] = element; //Add new component
}