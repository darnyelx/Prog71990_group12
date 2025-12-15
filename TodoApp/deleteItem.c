#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

/*
 * Deletes an item from the list based on its ID.
 *
 * Parameters:
 *   items - pointer to the ItemList containing the items
 *   id    - ID of the item to delete
 *
 * Returns:
 *   A dynamically allocated copy of the deleted item if found,
 *   or NULL if the item does not exist or deletion fails.
 *
 * Notes:
 *   - The caller is responsible for freeing the returned Item.
 *   - The items list is compacted after deletion.
 *
 * Author: ""
 */
Item* deleteItemById(ItemList* items, int id)
{
    // Validate input list
    if (items == NULL || items->data == NULL || items->count == 0) {
        return NULL;
    }

    // Locate the index of the item with the matching ID
    size_t foundIndex = 0;
    int found = 0;

    for (size_t i = 0; i < items->count; i++) {
        if (items->data[i].id == id) {
            foundIndex = i;
            found = 1;
            break;
        }
    }

    // If the item was not found, return NULL
    if (!found) {
        return NULL;
    }

    // Allocate memory to store a copy of the item being deleted
    Item* deletedItem = malloc(sizeof(Item));
    if (deletedItem == NULL) {
        return NULL;
    }

    // Copy the item data before removing it from the list
    *deletedItem = items->data[foundIndex];

    // Shift all items after the deleted item one position to the left
    // This keeps the array contiguous
    for (size_t i = foundIndex; i < items->count - 1; i++) {
        items->data[i] = items->data[i + 1];
    }

    // Reduce the total item count
    items->count--;

    // Optionally shrink the array if a lot of space is unused
    if (items->count > 0 && items->count <= items->capacity / 4) {
        size_t newCapacity = items->capacity / 2;

        // Prevent shrinking below a reasonable minimum capacity
        if (newCapacity >= 10) {
            Item* resizedData = realloc(items->data, newCapacity * sizeof(Item));
            if (resizedData != NULL) {
                items->data = resizedData;
                items->capacity = newCapacity;
            }
        }
    }

    // Return the deleted item (caller must free it)
    return deletedItem;
}
