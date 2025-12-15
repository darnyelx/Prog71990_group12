
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

Item* deleteItemById(ItemList* items, int id) {
    if (items == NULL || items->data == NULL || items->count == 0) {
        return NULL;
    }
    
    // Find the item to delete
    int foundIndex = -1;
    for (size_t i = 0; i < items->count; i++) {
        if (items->data[i].id == id) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex == -1) {
        return NULL; // Item not found
    }
    
    // Create a copy of the item to return before deletion
    Item* deletedItem = (Item*)malloc(sizeof(Item));
    if (deletedItem == NULL) {
        return NULL;
    }
    *deletedItem = items->data[foundIndex];
    
    // Shift all items after the found index one position to the left
    for (size_t i = foundIndex; i < items->count - 1; i++) {
        items->data[i] = items->data[i + 1];
    }
    
    // Decrease the count
    items->count--;
    
    // Optionally shrink the array if it's significantly underutilized
    if (items->count > 0 && items->count <= items->capacity / 4) {
        size_t newCapacity = items->capacity / 2;
        if (newCapacity >= 10) { // Don't shrink below minimum capacity
            Item* newData = (Item*)realloc(items->data, newCapacity * sizeof(Item));
            if (newData != NULL) {
                items->data = newData;
                items->capacity = newCapacity;
            }
        }
    }
    
    return deletedItem;
}
