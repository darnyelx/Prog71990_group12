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

/*
 * Displays a list of items filtered by a search term and allows user interaction.
 *
 * Parameters:
 *   filteredItems - pointer to an ItemList used to store filtered results
 *   allItems      - pointer to the complete ItemList
 *   searchTerm    - keyword used to filter items by title or details
 *
 * Behavior:
 *   - Builds a filtered list based on the search term
 *   - Displays the filtered items in a table format
 *   - Allows the user to select an item by ID or return to the full list
 *
 * Notes:
 *   - Filtering is case-sensitive
 *   - filteredItems is reused and rebuilt on each call
 *
 * Author: Kadeema Wakha
 */
void viewFilteredItems(ItemList* filteredItems, ItemList* allItems, const char* searchTerm)
{
    clearScreen();

    int i;
    int selection = -2;

    // Validate that the full item list exists
    if (allItems == NULL || allItems->count == 0) {
        printf("No items available.\n");
        return;
    }

    /* Reset filtered list before rebuilding it */
    filteredItems->count = 0;

    /* Build filtered list based on search term in title or details */
    for (i = 0; i < allItems->count; i++) {
        if (strstr(allItems->data[i].title, searchTerm) != NULL ||
            strstr(allItems->data[i].details, searchTerm) != NULL) {

            filteredItems->data[filteredItems->count] = allItems->data[i];
            filteredItems->count++;
        }
    }

    /* Display filtered items header */
    printf("\n==============================================\n");
    printf("          FILTERED TODOs FOR \"%s\"\n", searchTerm);
    printf("==============================================\n\n");

    /* Display table header */
    printf("+----+----------------------+----------------------+------------+------------+\n");
    printf("| ID | Title                | Content              | Status     | Created    |\n");
    printf("+----+----------------------+----------------------+------------+------------+\n");

    /* Display each filtered item */
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

    /* Prompt user to select an item or return */
    promptSelectAFilteredItem(&selection);

    switch (selection) {

        case 0:
            /* Return to full items view */
            viewItems(allItems, 0);
            break;

        default: {
            /* Attempt to retrieve selected item by ID */
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
