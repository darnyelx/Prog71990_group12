#include <stdio.h>
#include "promptSearchTerm.h"
#include "ItemsSearcher.h"
#include "ViewFilteredItems.h"
#include "ViewItemDetails.h"
#include "getItemById.h"
#include "promptItemSelection.h"
#include "Item.h"

void viewItems(struct ItemList* items) {
	// clear screen
	printf("\n==================== TODO LIST ====================\n");

	// view list of items
	printf("0. Back\n");
	printf("-1. Search\n");

	for (int i = 0; i < items->count; i++) {
		printf("%d. %s\n",
			items->items[i].id,
			items->items[i].name);
	}

	int selection = -2;
	promptItemSelection(&selection);

	switch (selection) {

	case 0:
		// free items (if dynamically allocated elsewhere)
		// go back to welcome
		welcome(items);
		break;

	case -1: {
		char searchTerm[100];
		promptSearchTerm(searchTerm);
		ItemList* filteredItems = itemsSearcher(searchTerm);
		viewFilteredItems(filteredItems, items, searchTerm);
		break;
	}

	default:
		// check if item exists
		viewItemDetails(getItemById(items, selection), items);
		break;
	}
}
