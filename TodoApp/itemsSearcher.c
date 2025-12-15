#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

#define INITIAL_CAPACITY 5

ItemList* itemsSearcher(ItemList* items, char* term)
{
    if (!items || !term) {
        return NULL;
    }

    ItemList* result = malloc(sizeof(ItemList));
    if (!result) return NULL;

    result->count = 0;
    result->capacity = INITIAL_CAPACITY;
    result->data = malloc(sizeof(Item) * result->capacity);

    if (!result->data) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < items->count; i++)
    {
        Item* current = &items->data[i];

        // search in title OR details
        if (strstr(current->title, term) || strstr(current->details, term))
        {
            // grow result list if needed
            if (result->count == result->capacity) {
                result->capacity *= 2;
                Item* temp = realloc(result->data,
                    sizeof(Item) * result->capacity);
                if (!temp) {
                    free(result->data);
                    free(result);
                    return NULL;
                }
                result->data = temp;
            }

            // copy item into result list
            result->data[result->count++] = *current;
        }
    }

    return result;
}
