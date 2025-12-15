#include <stdio.h>

#include "Item.h"
#include "ViewFilteredItems.h"
#include "promptItemSelection.h"
#include "ViewItemDetails.h"
#include "getItemById.h"
#include "ViewItems.h"
#include "promptSelectAFilteredItem.h"




void viewFilteredItems( ItemList* filteredItems,  ItemList* allItems, const char* searchTerm ) {
	//show filtered items based on search term


	int selection = -2;

	promptSelectAFilteredItem(&selection);


	switch (selection) {

	case 0: {
		//free filteredItems
		//go back to all items view
		void viewItems();
	}
		  break;

	default:
		viewItemDetails(getItemById(allItems, selection));
		break;
	}
}