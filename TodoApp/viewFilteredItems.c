#include <stdio.h>
#include <string.h>

#include "Item.h"
#include "ViewFilteredItems.h"
#include "promptItemSelection.h"
#include "ViewItemDetails.h"
#include "getItemById.h"
#include "ViewItems.h"
#include "promptSelectAFilteredItem.h"
#include "promptSearchTerm.h"

void viewFilteredItems(ItemList* filteredItems, ItemList* allItems, const char* searchTerm) {
    clearScreen();
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
    printf("\n==============================================\n");
    printf("          FILTERED TODOs FOR \"%s\"\n", searchTerm);
    printf("==============================================\n");
    printf("\n");

    printf("+----+----------------------+----------------------+------------+------------+\n");
    printf("| ID | Title                | Content              | Status     | Created    |\n");
    printf("+----+----------------------+----------------------+------------+------------+\n");

    for (i = 0; i < filteredItems->count; i++) {
        Item* item = &filteredItems->data[i];

        printf("| %-2d | %-20s | %-20s | %-10s | %-10s |\n",
            item->id,
            item->title,
            item->details,
            item->status,
            item->created);
    }

    printf("+----+----------------------+----------------------+------------+------------+\n");


        promptSelectAFilteredItem(&selection);
    


    switch (selection) {

    case 0:
		//free filteredItems;

        /* go back to all items view */
        viewItems(allItems, 0);
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
