#include <stdio.h>
#include "promptSearchTerm.h"
#include "ItemsSearcher.h"
#include "ViewFilteredItems.h"
#include "ViewItemDetails.h"
#include "getItemById.h"
#include "promptItemSelection.h"
#include "Item.h"

void viewItems(struct ItemList* items) {
	//clear screen
	//view list of items
	int selection = -2;

	promptItemSelection(&selection);
	

	switch (selection) {

		case 0: {
			//free items
			//go back to welcome
			void welcome();
		}
			  break;
		case -1: {
			char searchTerm[100];
			promptSearchTerm(searchTerm);
			ItemList* filteredItems = itemsSearcher(searchTerm);
			viewFilteredItems(filteredItems, items, searchTerm);
		}

			  break;
		default:
			viewItemDetails(getItemById(items, selection));
			break;
	}

	
}