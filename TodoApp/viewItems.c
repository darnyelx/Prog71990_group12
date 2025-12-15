#include <stdio.h>
#include "ViewItems.h"
#include "Item.h"
#include "ViewItemDetails.h"

void viewItems(ItemList* items) {
    if (items == NULL || items->count == 0) {
        printf("\nNo items to display.\n");
        return;
    }

    printf("\n=============== ITEMS ===============\n");
    printf(" ID   | Title                | Status\n");
    printf("-------------------------------------\n");

    for (size_t i = 0; i < items->count; i++) {
        printf(" %-4d | %-20s | %s\n",
            items->data[i].id,
            items->data[i].title,
            items->data[i].status);
    }

    printf("=====================================\n");

    // Prompt user to view item details
    int id;
    printf("\nEnter an item ID to view details (0 to go back): ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        return;
    }

    if (id == 0) {
        return;
    }

    // Find selected item
    Item* selectedItem = NULL;
    for (size_t i = 0; i < items->count; i++) {
        if (items->data[i].id == id) {
            selectedItem = &items->data[i];
            break;
        }
    }

    // Show item details
    viewItemDetails(selectedItem, items);
}
