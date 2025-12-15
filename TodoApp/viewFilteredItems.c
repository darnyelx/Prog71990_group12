#include <stdio.h>
#include <string.h>

#include "Item.h"
#include "ViewFilteredItems.h"
#include "promptItemSelection.h"
#include "ViewItemDetails.h"
#include "getItemById.h"
#include "ViewItems.h"
#include "promptSelectAFilteredItem.h"

void viewFilteredItems(ItemList* filteredItems, ItemList* allItems, const char* searchTerm) {
    int i;
    int selection = -2;

    if (allItems == NULL || allItems->count == 0) {
        printf("No items available.\n");
        return;
    }

    /* clear filtered list */
    filteredItems->count = 0;

    /* build filtered list based on search term in title or details */
    for (i = 0; i < allItems->count; i++) {
        if (strstr(allItems->data[i].title, searchTerm) != NULL ||
            strstr(allItems->data[i].details, searchTerm) != NULL) {
            filteredItems->data[filteredItems->count] = allItems->data[i];
            filteredItems->count++;
        }
    }

    /* display filtered items */
    printf("\nFiltered Items for \"%s\"\n", searchTerm);
    printf("0. Back\n");

    if (filteredItems->count == 0) {
        printf("No matching items found.\n");
    }
    else {
        for (i = 0; i < filteredItems->count; i++) {
            Item* item = &filteredItems->data[i];
            printf("\n---------------------------------\n");
            printf("ID: %d\n", item->id);
            printf("Title: %s\n", item->title);
            printf("Content: %s\n", item->details);
            printf("Status: %s\n", item->status);
            printf("Created at: %s\n", item->created); 
            printf("---------------------------------\n");
        }
    }

    promptSelectAFilteredItem(&selection);

    switch (selection) {

    case 0:
        /* clear filteredItems */
        filteredItems->count = 0;

        /* go back to all items view */
        viewItems(allItems);
        break;

    default: {
        Item* item = getItemById(allItems, selection);

        if (item != NULL) {
            viewItemDetails(item, allItems);
        }
        else {
            printf("Invalid selection.\n");
            viewFilteredItems(filteredItems, allItems, searchTerm);
        }
        break;
    }
    }
}
