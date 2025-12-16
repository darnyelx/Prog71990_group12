#include <stdio.h>
#include "Item.h"

/*
 * Retrieves an item from the list based on its ID.
 *
 * Parameters:
 *   items - pointer to the ItemList containing the items
 *   id    - ID of the item to retrieve
 *
 * Returns:
 *   A pointer to the matching Item if found,
 *   or NULL if the item does not exist.
 *
 * Notes:
 *   - The returned pointer refers to the item inside the list.
 *   - The caller must NOT free the returned pointer.
 *
 * Author: "Chiemeke Ifeanyi"
 */
Item* getItemById(ItemList* items, int id)
{
    // Validate the items list
    if (items == NULL || items->data == NULL) {
        return NULL;
    }

    // Search through the list for the matching ID
    for (size_t i = 0; i < items->count; i++) {
        if (items->data[i].id == id) {
            // Return address of the item inside the list
            return &items->data[i];
        }
    }

    // Item not found
    return NULL;
}
