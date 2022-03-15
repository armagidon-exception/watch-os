#pragma once
#include "stdlib.h"
#include "stdint.h"

#define add_element_uni(list, element, type) \
                    if ((list)->__element_head > (list)->__initial_capacity - 1) \
                        (list)->array = realloc((list)->array, (list)->__element_size * ((list)->__element_head + 1)); \
                    ((type*) (list)->array)[(list)->__element_head++] = element;
                    


typedef struct List {
    void* array;
    uint8_t __element_head;
    uint8_t __element_size;
    uint8_t __initial_capacity;
} ArrayList;

List create_arraylist(uint8_t __initial_capacity, uint8_t __element_size);
List create_int_arraylist(uint8_t __initial_capacity);
void *get_element(List* list, uint8_t index);
void for_each_copied(List list, void (*action)(void* context)); //Iterate through all elements of the copy of the list
void for_each(List* list, void (*action)(void* context)); //Iterate through all elements of the list
void add_int(List* list, uint8_t element);
uint8_t reduce(List* list, uint8_t (*accumulator)(uint8_t, uint8_t));
//List filter(List* list, bool (*predicate)(void* context));
void deleteList(List* list);