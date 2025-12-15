#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Item.h"
#include "getItemById.h"

// Memory management functions
ItemList* createItemList(size_t initialCapacity) {
    if (initialCapacity == 0) {
        initialCapacity = INITIAL_CAPACITY;
    }
    
    ItemList* list = (ItemList*)malloc(sizeof(ItemList));
    if (list == NULL) {
        return NULL;
    }
    
    list->data = (Item*)malloc(initialCapacity * sizeof(Item));
    if (list->data == NULL) {
        free(list);
        return NULL;
    }
    
    list->count = 0;
    list->capacity = initialCapacity;
    
    return list;
}

void freeItemList(ItemList* list) {
    if (list != NULL) {
        if (list->data != NULL) {
            free(list->data);
        }
        free(list);
    }
}

int ensureCapacity(ItemList* list, size_t minCapacity) {
    if (list == NULL || list->data == NULL) {
        return 0;
    }
    
    if (list->capacity >= minCapacity) {
        return 1;
    }
    
    // Double the capacity until it's sufficient
    size_t newCapacity = list->capacity;
    while (newCapacity < minCapacity) {
        newCapacity *= 2;
    }
    
    Item* newData = (Item*)realloc(list->data, newCapacity * sizeof(Item));
    if (newData == NULL) {
        return 0;
    }
    
    list->data = newData;
    list->capacity = newCapacity;
    
    return 1;
}

int addItem(ItemList* list, const Item* item) {
    if (list == NULL || item == NULL) {
        return 0;
    }
    
    if (!ensureCapacity(list, list->count + 1)) {
        return 0;
    }
    
    list->data[list->count] = *item;
    list->count++;
    
    return 1;
}

void removeItemAt(ItemList* list, size_t index) {
    if (list == NULL || index >= list->count) {
        return;
    }
    
    // Shift items left
    for (size_t i = index; i < list->count - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    
    list->count--;
}

// Item management functions
Item createItem(int id, const char* title, const char* details, const char* status) {
    Item item;
    item.id = id;
    
    if (title != NULL) {
        strncpy_s(item.title, title, MAX_TITLE_LENGTH - 1);
        item.title[MAX_TITLE_LENGTH - 1] = '\0';
    } else {
        item.title[0] = '\0';
    }
    
    if (details != NULL) {
        strncpy_s(item.details, details, MAX_DETAILS_LENGTH - 1);
        item.details[MAX_DETAILS_LENGTH - 1] = '\0';
    } else {
        item.details[0] = '\0';
    }
    
    if (status != NULL) {
        strncpy_s(item.status, status, MAX_STATUS_LENGTH - 1);
        item.status[MAX_STATUS_LENGTH - 1] = '\0';
    } else {
        strcpy_s(item.status, "Pending");
    }
    
    getCurrentDateString(item.created, MAX_DATE_LENGTH);
    
    return item;
}
/*
Item* getItemById(ItemList* list, int id) {
    if (list == NULL || list->data == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < list->count; i++) {
        if (list->data[i].id == id) {
            return &list->data[i];
        }
    }
    
    return NULL;
}*/

int updateItem(ItemList* list, int id, const Item* updatedItem) {
    Item* item = getItemById(list, id);
    if (item == NULL) {
        return 0;
    }
    
    *item = *updatedItem;
    return 1;
}

int deleteItem(ItemList* list, int id) {
    if (list == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < list->count; i++) {
        if (list->data[i].id == id) {
            removeItemAt(list, i);
            return 1;
        }
    }
    
    return 0;
}

// Utility functions
void getCurrentDateString(char* buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return;
    }
    
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    
    if (tm_info != NULL) {
        strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
    } else {
        strcpy_s(buffer, "Unknown");
    }
}

int validateItem(const Item* item) {
    if (item == NULL) {
        return 0;
    }
    
    if (item->id < 0) {
        return 0;
    }
    
    if (strlen(item->title) == 0) {
        return 0;
    }
    
    if (strlen(item->status) == 0) {
        return 0;
    }
    
    return 1;
}
