#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Item.h"
#include "getItemById.h"

/* ============================================================
   ITEM LIST MEMORY MANAGEMENT
   ============================================================ */

   /*
    * Creates and initializes an ItemList with a given capacity.
    *
    * Parameters:
    *   initialCapacity - starting size of the list
    *
    * Returns:
    *   Pointer to a newly allocated ItemList, or NULL on failure.
    */
ItemList* createItemList(size_t initialCapacity)
{
    if (initialCapacity == 0) {
        initialCapacity = INITIAL_CAPACITY;
    }

    ItemList* list = malloc(sizeof(ItemList));
    if (list == NULL) {
        return NULL;
    }

    list->data = malloc(initialCapacity * sizeof(Item));
    if (list->data == NULL) {
        free(list);
        return NULL;
    }

    list->count = 0;
    list->capacity = initialCapacity;
    return list;
}

/*
 * Frees all memory associated with an ItemList.
 */
void freeItemList(ItemList* list)
{
    if (list != NULL) {
        free(list->data);
        free(list);
    }
}

/*
 * Ensures the list has at least the specified capacity.
 * Automatically resizes the list if required.
 */
int ensureCapacity(ItemList* list, size_t minCapacity)
{
    if (list == NULL || list->data == NULL) {
        return 0;
    }

    if (list->capacity >= minCapacity) {
        return 1;
    }

    size_t newCapacity = list->capacity;
    while (newCapacity < minCapacity) {
        newCapacity *= 2;
    }

    Item* newData = realloc(list->data, newCapacity * sizeof(Item));
    if (newData == NULL) {
        return 0;
    }

    list->data = newData;
    list->capacity = newCapacity;
    return 1;
}

/*
 * Adds a new item to the list.
 */
int addItem(ItemList* list, const Item* item)
{
    if (list == NULL || item == NULL) {
        return 0;
    }

    if (!ensureCapacity(list, list->count + 1)) {
        return 0;
    }

    list->data[list->count++] = *item;
    return 1;
}

/*
 * Removes an item at a specific index by shifting remaining items.
 */
void removeItemAt(ItemList* list, size_t index)
{
    if (list == NULL || index >= list->count) {
        return;
    }

    for (size_t i = index; i < list->count - 1; i++) {
        list->data[i] = list->data[i + 1];
    }

    list->count--;
}

/* ============================================================
   ITEM MANAGEMENT
   ============================================================ */

   /*
    * Creates a new Item with the provided values.
    * Automatically sets the creation date.
    */
Item createItem(int id, const char* title, const char* details, const char* status)
{
    Item item;
    item.id = id;

    if (title) {
        strncpy_s(item.title, sizeof(item.title), title, sizeof(item.title) - 1);
        item.title[sizeof(item.title) - 1] = '\0';
    }
    else {
        item.title[0] = '\0';
    }

    if (details) {
        strncpy_s(item.details, sizeof(item.details), details, sizeof(item.details) - 1);
        item.details[sizeof(item.details) - 1] = '\0';
    }
    else {
        item.details[0] = '\0';
    }

    if (status) {
        strncpy_s(item.status, sizeof(item.status), status, sizeof(item.status) - 1);
        item.status[sizeof(item.status) - 1] = '\0';
    }
    else {
        strcpy_s(item.status, sizeof(item.status), "Pending");
    }

    getCurrentDateString(item.created, MAX_DATE_LENGTH);
    return item;
}

/*
 * Updates an existing item identified by ID.
 */
int updateItem(ItemList* list, int id, const Item* updatedItem)
{
    Item* item = getItemById(list, id);
    if (item == NULL) {
        return 0;
    }

    *item = *updatedItem;
    return 1;
}

/*
 * Deletes an item from the list by ID.
 */
int deleteItem(ItemList* list, int id)
{
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

/* ============================================================
   UTILITY FUNCTIONS
   ============================================================ */

   /*
    * Writes the current date and time into the provided buffer.
    */
void getCurrentDateString(char* buffer, size_t size)
{
    if (buffer == NULL || size == 0) {
        return;
    }

    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);

    if (tm_info) {
        strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
    }
    else {
        strcpy_s(buffer, size, "Unknown");
    }
}

/*
 * Validates required fields of an Item.
 */
int validateItem(const Item* item)
{
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

/*
 * Clears the terminal screen.
 */
void clearScreen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
