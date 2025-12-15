
#ifndef ITEM_H
#define ITEM_H

#include <time.h>

#define INITIAL_CAPACITY 10
#define MAX_TITLE_LENGTH 50
#define MAX_DETAILS_LENGTH 1000
#define MAX_STATUS_LENGTH 20
#define MAX_DATE_LENGTH 20

typedef struct Item {
    int id;
    char title[MAX_TITLE_LENGTH];
    char details[MAX_DETAILS_LENGTH];
    char created[MAX_DATE_LENGTH];
    char status[MAX_STATUS_LENGTH];
} Item;

typedef struct {
    Item* data;
    size_t count;
    size_t capacity;
} ItemList;

// Memory management functions
ItemList* createItemList(size_t initialCapacity);
void freeItemList(ItemList* list);
int ensureCapacity(ItemList* list, size_t minCapacity);
int addItem(ItemList* list, const Item* item);
void removeItemAt(ItemList* list, size_t index);

// Item management functions
Item createItem(int id, const char* title, const char* details, const char* status);
//Item* getItemById(ItemList* list, int id);
int updateItem(ItemList* list, int id, const Item* updatedItem);
int deleteItem(ItemList* list, int id);

// Utility functions
void getCurrentDateString(char* buffer, size_t size);
int validateItem(const Item* item);

#endif
