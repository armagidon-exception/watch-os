#include "custom_data_storage.h"
#include "Arduino.h"

DataStorage allocate_storage() {
    DataStorage storage = {0, (uint8_t*) calloc(1, sizeof(uint8_t)), nullptr};
    if (storage.offsets == nullptr) {
        Serial.println("not enough memory");
    }
    return storage;
}

static uint8_t sum(uint8_t* ptr, uint8_t end) {
    uint8_t sum = 0;
    for (uint8_t i = 0; i <= end; i++)
        sum += ptr[i];
    return sum;
}

void put_to_storage(DataStorage* storage, void* element, uint8_t size) {
    //Add offset
    storage->size++;
    storage->offsets = (uint8_t*) realloc(storage->offsets, sizeof(uint8_t) * storage->size);
    storage->offsets[storage->size - 1] = size;
    //Allocate space for new data
    auto offset = sum(storage->offsets, storage->size - 1) - size;
    storage->data = realloc(storage->data, offset + size);
    //Find where to set the data
    uint8_t* valptr = (uint8_t*) element;
    uint8_t* cursor = (uint8_t*) (storage->data + offset);
    for (uint8_t i = 0; i < size; i++)
        cursor[i] = valptr[i];
}


void* get_from_storage(DataStorage* storage, uint8_t index) {
    auto offset = 0;
    if (index > 0) {
        offset = sum(storage->offsets, index - 1);
    }
    return storage->data + offset;
}

void dispose_storage(DataStorage* storage) {
    free(storage->data);
    free(storage->offsets);
}