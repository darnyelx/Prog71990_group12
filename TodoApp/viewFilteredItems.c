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
	// show filtered items based on search term

	int i;
	int selection = -2;

	/* clear filtered list */
	filteredItems->count = 0;

	/* filter items */
	for (i = 0; i < allItems->count; i++) {
		if (strstr(allItems->items[i].name, searchTerm) != NULL) {
			filteredItems->items[filteredItems->count] =
				allItems->items[i];
			filteredItems->count++;
		}
	}

	/* display filtered items */
	printf("\nFiltered Items for \"%s\"\n", searchTerm);
	printf("0. Back\n");

	for (i = 0; i < filteredItems->count; i++) {
		printf("%d. %s\n",
			filteredItems->items[i].id,
			filteredItems->items[i].name);
	}

	promptSelectAFilteredItem(&selection);

	switch (selection) {

	case 0:
		/* free filteredItems (logical clear) */
		filteredItems->count = 0;

		/* go back to all items view */
		viewItems(allItems);
		break;

	default: {
		Item* item = getItemById(allItems, selection);

		if (item != NULL) {
			viewItemDetails(item);
		}
		else {
			printf("Invalid selection.\n");
			viewFilteredItems(filteredItems, allItems, searchTerm);
		}
		break;
	}
	}
}
