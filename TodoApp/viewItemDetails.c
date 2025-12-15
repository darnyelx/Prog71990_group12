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

void viewItemDetails(Item* item, ItemList* items) {
	// display item details

	if (item == NULL) {
		printf("Item not found.\n");
		viewItems(items);
		return;
	}

	printf("\n============= ITEM DETAILS =============\n");
	printf("ID: %d\n", item->id);
	printf("Name: %s\n", item->title);
	printf("Status: %s\n", item->status);
	printf("========================================\n");

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
			printf("Item deleted successfully.\n");
			viewItems(items);
		}
		else {
			viewItemDetails(item, items);
		}
		break;
	}

	case 3:
		// change status
		promptChangeItemStatus(*item);
		saveToDisk(items);
		printf("Item status updated.\n");
		viewItemDetails(item, items);
		break;

	default:
		// refresh item details
		viewItemDetails(item, items);
		break;
	}
}
