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
	clearScreen();

	if (item == NULL) {
		printf("Item not found.\n");
		viewItems(items, 0);
		return;
	}

	printf("\n");
	printf("+------------------------------------------+\n");
	printf("|              ITEM DETAILS                |\n");
	printf("+------------------------------------------+\n");
	printf("| ID      : %-30d |\n", item->id);
	printf("| Name    : %-30s |\n", item->title);
	printf("| Details : %-30s |\n", item->details);
	printf("| Status  : %-30s |\n", item->status);
	printf("+------------------------------------------+\n");


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
		printf("Item status updated.\n");
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
