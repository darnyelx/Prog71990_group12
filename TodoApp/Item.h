#ifndef ITEM_H
#define ITEM_H

typedef struct Item {
    int id;
    char title[50];
    char items[300];
    char created[20];
    char updated[20];
    char status[20];
} Item;

#endif
