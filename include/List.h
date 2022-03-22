#pragma once
#include "stdlib.h"
#include "stdint.h"

typedef struct List {
    void* array;
    const char** ids;
    uint8_t __element_head;
    uint8_t __element_size;
    uint8_t __initial_capacity;
} ArrayList;

List create_arraylist(uint8_t __initial_capacity, uint8_t __element_size);
List create_int_arraylist(uint8_t __initial_capacity);
void *get_element(List* list, uint8_t index);
void *get_element_by_id(List* list, const char* id);
void for_each_copied(List list, void (*action)(void* context)); //Iterate through all elements of the copy of the list
void for_each(List* list, void (*action)(void* context)); //Iterate through all elements of the list
void add_int(List* list, uint8_t element);
uint8_t add_element(List*, void*);
void add_element_with_id(List*, void*, const char*);
uint8_t reduce(List* list, uint8_t (*accumulator)(uint8_t, uint8_t));
void deleteList(List* list);