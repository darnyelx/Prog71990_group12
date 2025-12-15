#ifndef ITEM_H
#define ITEM_H

typedef struct Item {
    int id;
    char title[50];
    char details[1000];
    char created[20];
    char status[20];
} Item;

typedef struct {
    Item* data;
    size_t count;
    size_t capacity;
} ItemList;

#endif
