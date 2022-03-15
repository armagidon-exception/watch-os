#pragma once
#include "List.h"

typedef struct {
    uint8_t size;
    uint8_t* offsets;
    void *data;
} DataStorage;

DataStorage allocate_storage(void);
void put_to_storage(DataStorage* storage, void* element, uint8_t size);
void* get_from_storage(DataStorage* storage, uint8_t index);