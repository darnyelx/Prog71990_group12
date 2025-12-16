#include <stdio.h>
#include "ViewItems.h"
#include "Item.h"
#include "ViewItemDetails.h"
#include "promptItemSelection.h"
#include "welcome.h"
#include "promptSearchTerm.h"
#include "itemsSearcher.h"
#include "ViewFilteredItems.h"
#include "viewSearcher.h"

/*
 * Displays all Todo items and allows the user to interact with them.
 *
 * Parameters:
 *   items - pointer to the ItemList containing all Todo items
 *   error - status flag used to display contextual messages:
 *           0 -> no error
 *           1 -> no items found from a previous search
 *           2 -> search term was empty
 *
 * Behavior:
 *   - Displays a list of all Todo items in a table format
 *   - Shows optional search-related messages based on the error flag
 *   - Allows the user to select an item ID, search, return to menu, or exit
 *
 * Author: Kadeema Wakha
 */
void viewItems(ItemList* items, int error)
{
    clearScreen();

    if (items == NULL || items->count == 0) {
        printf("\nNo items to display.\n");
        return;
    }

    /* Optional messages */
    if (error == 1) {
        printf("\n=================================\n");
        printf("           SEARCH RESULT          \n");
        printf("=================================\n");
        printf("No items found matching your\n");
        printf("previous search.\n");
        printf("=================================\n\n");
    }
    else if (error == 2) {
        printf("\n=================================\n");
        printf("              SEARCH             \n");
        printf("=================================\n");
        printf("Search term cannot be empty.\n");
        printf("Please enter a keyword.\n");
        printf("=================================\n\n");
    }

    /* Main list header */
    printf("\n=================================\n");
    printf("              TODOS              \n");
    printf("=================================\n");

    /* Table header */
    printf("+------+----------------------+--------------+\n");
    printf("| ID   | Title                | Status       |\n");
    printf("+------+----------------------+--------------+\n");

    /* Table rows */
    for (size_t i = 0; i < items->count; i++) {
        printf("| %-4d | %-20s | %-12s |\n",
               items->data[i].id,
               items->data[i].title,
               items->data[i].status);
    }

    printf("+------+----------------------+--------------+\n");

    /* Prompt user to view item details */
    int id;
    promptItemSelection(&id);

    if (id == 0) {
        welcome(items);
        return;
    }

    if (id == -1) {
        viewSearcher(items, 0);
        exit(1);
        return;
    }

    /* Find selected item */
    Item* selectedItem = NULL;
    for (size_t i = 0; i < items->count; i++) {
        if (items->data[i].id == id) {
            selectedItem = &items->data[i];
            break;
        }
    }

    /* Show item details */
    viewItemDetails(selectedItem, items);
}
