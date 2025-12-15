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

void viewItemDetails(Item* item, Item** items) {
	//implement view item details

	int selection = 0;
	promptSingleItemAction(&selection);
	
	switch (selection) {
		case 1:
			promptEditItem(item);
			saveToDisk(items);
			//prompt success message
			viewItemDetails(item, items);
			break;
		case 2: {
			int promptDeleteItemSelection = 0;
			promptDeleteItem(&promptDeleteItemSelection);
			if (promptDeleteItemSelection == 1) {
				deleteItemById(items, promptDeleteItemSelection);
				//free item memory
				//show success message
				//go back to view items
				viewItems(items);
			}

		}

			break;
		case 3:{
			promptChangeItemStatus(*item);
			saveToDisk(items);
			//prompt success message
			//show view item details again
			viewItemDetails(item, items);
		}

			break;

		default: {
			//go back to view items
			viewItems(items);
		}
			  break;
		
	}
}