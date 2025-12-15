#include <stdio.h>
#include "Item.h"

Item* getItemById(ItemList* items, int id)
{
    if (!items || !items->data) {
        return NULL;
    }

    for (size_t i = 0; i < items->count; i++) {
        if (items->data[i].id == id) {
            return &items->data[i];  // return pointer to the found item
        }
    }

    return NULL; // not found
}
