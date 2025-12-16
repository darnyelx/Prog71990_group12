#include <stdio.h>
#include <string.h>
#include "Item.h"
#include "viewItems.h"
#include "promptSearchTerm.h"
#include "itemsSearcher.h"
#include "ViewFilteredItems.h"

/*
 * Handles searching for Todo items based on a user-provided search term.
 *
 * Parameters:
 *   items - pointer to the ItemList containing all Todo items
 *   error - status flag (currently unused directly in this function)
 *
 * Behavior:
 *   - Prompts the user to enter a search term
 *   - If the search term is empty, returns to the items view with an error message
 *   - Filters items by title or details using the search term
 *   - Displays filtered results if matches are found
 *   - Returns to the items view with an error message if no matches are found
 *
 * Author: Kadeema Wakha
 */
void viewSearcher(ItemList* items, int error)
{
	clearScreen();

	char searchTerm[100];

	/* Prompt user for search term */
	promptSearchTerm(searchTerm);

	/* Check for empty search term */
	if (strlen(searchTerm) == 0) {
		viewItems(items, 2);
		return;
	}

	/* Create filtered items list based on search term */
	ItemList* filteredItems = itemsSearcher(items, searchTerm);

	/* Display results if any items matched */
	if (filteredItems->count > 0) {
		viewFilteredItems(filteredItems, items, searchTerm);
	}
	else {
		/* No matching items found */
		viewItems(items, 1);
	}
}
