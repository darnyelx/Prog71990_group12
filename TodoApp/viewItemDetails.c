#include <stdio.h>
#include "ViewItemDetails.h"
#include "Item.h"
#include "promptSingleItemAction.h"
#include "promptEditItem.h"
#include "saveToDisk.h"
#include "promptDeleteItem.h"
#include "deleteItem.h"
#include "promptChangeItemStatus.h"
#include "ViewItems.h"

void viewItemDetails(Item* item, ItemList* items)
{
    clearScreen();

    if (item == NULL) {
        printf("Todo not found.\n");
        viewItems(items, 0);
        return;
    }

    /* Consistent header style */
    printf("\n=================================\n");
    printf("           Todo DETAILS          \n");
    printf("=================================\n");

    /* Consistent details layout */
    printf("ID      : %d\n", item->id);
    printf("Title   : %s\n", item->title);
    printf("Details : %s\n", item->details);
    printf("Status  : %s\n", item->status);
    printf("---------------------------------\n");

    int selection = 0;
    promptSingleItemAction(&selection);

    switch (selection) {

        case 1:
            // edit item
            promptEditItem(item);
            saveToDisk(items);
            printf("Item updated successfully.\n");
            viewItemDetails(item, items);
            break;

        case 2: {
            int promptDeleteItemSelection = 0;
            promptDeleteItem(&promptDeleteItemSelection);

            if (promptDeleteItemSelection == 1) {
                deleteItemById(items, item->id);
                saveToDisk(items);
                printf("Todo deleted successfully.\n");
                viewItems(items, 0);
            }
            else {
                viewItemDetails(item, items);
            }
            break;
        }

        case 3:
            // change status
            promptChangeItemStatus(item);
            saveToDisk(items);
            printf("Todo status updated.\n");
            viewItemDetails(item, items);
            break;

        case 0:
            // back to all items
            viewItems(items, 0);
            break;

        default:
            // refresh item details
            viewItemDetails(item, items);
            break;
    }
}
