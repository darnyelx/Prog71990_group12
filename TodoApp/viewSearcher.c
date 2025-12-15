#include <stdio.h>
#include <string.h>
#include "Item.h"
#include "viewItems.h"
#include "promptSearchTerm.h"
#include "itemsSearcher.h"
#include "ViewFilteredItems.h"

void viewSearcher(ItemList* items, int error) {
	 
	 clearScreen();
	


	 char searchTerm[100];
	 
	
	 promptSearchTerm(searchTerm);
	 //check if it's not empty
	 if (strlen(searchTerm) == 0) {
		 viewItems(items, 2);
		 return;
	 }

	

	 //create a filtered items list and view it
	 ItemList* filteredItems = itemsSearcher(items, searchTerm);
	 if (filteredItems->count > 0)
	 {
		 viewFilteredItems(filteredItems, items, searchTerm);

	 } else {
		 viewItems(items, 1);
		
	 }
}