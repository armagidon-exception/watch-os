#pragma once
#include "stdlib.h"
#include "stdint.h"

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
void add_element(List*, void*);
uint8_t reduce(List* list, uint8_t (*accumulator)(uint8_t, uint8_t));
void deleteList(List* list);