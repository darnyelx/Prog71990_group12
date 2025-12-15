#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

#define INITIAL_CAPACITY 5

/*
 * Searches for items whose title or details contain the given search term.
 *
 * Parameters:
 *   items - pointer to the ItemList to search
 *   term  - search keyword
 *
 * Returns:
 *   A newly allocated ItemList containing matching items,
 *   or NULL if no items match or an error occurs.
 *
 * Notes:
 *   - The returned ItemList is dynamically allocated.
 *   - The caller is responsible for freeing the returned list.
 *   - Matching is case-sensitive.
 *
 * Author: ""
 */
ItemList* itemsSearcher(ItemList* items, char* term)
{
    // Validate input parameters
    if (items == NULL || term == NULL) {
        return NULL;
    }

    // Allocate memory for the result list
    ItemList* result = malloc(sizeof(ItemList));
    if (result == NULL) {
        return NULL;
    }

    // Initialize the result list
    result->count = 0;
    result->capacity = INITIAL_CAPACITY;
    result->data = malloc(sizeof(Item) * result->capacity);

    if (result->data == NULL) {
        free(result);
        return NULL;
    }

    // Iterate through all items in the original list
    for (size_t i = 0; i < items->count; i++) {
        Item* current = &items->data[i];

        // Check if the search term appears in the title or details
        if (strstr(current->title, term) != NULL ||
            strstr(current->details, term) != NULL)
        {
            // Resize the result list if capacity is reached
            if (result->count == result->capacity) {
                result->capacity *= 2;

                Item* resizedData = realloc(
                    result->data,
                    sizeof(Item) * result->capacity
                );

                if (resizedData == NULL) {
                    free(result->data);
                    free(result);
                    return NULL;
                }

                result->data = resizedData;
            }

            // Copy the matching item into the result list
            result->data[result->count++] = *current;
        }
    }

    // Return the list of matching items
    return result;
}
