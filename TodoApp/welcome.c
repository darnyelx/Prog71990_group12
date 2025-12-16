#include <stdio.h>
#include "welcome.h"
#include "promptWelcome.h"
#include "ViewItems.h"
#include "Item.h"
#include "promptCreateItem.h"

/*
 * Controls the main application flow based on the user's menu selection.
 *
 * Parameters:
 *   items - pointer to the ItemList containing all Todo items
 *
 * Behavior:
 *   - Displays the main menu
 *   - Routes the user to view items, create a new item, or exit the application
 *   - Re-prompts the menu on invalid selections
 *
 * Author: Ifeanyi Chiemeke
 */
void welcome(ItemList* items)
{
	int selection = 0;

	/* Display main menu and get user selection */
	promptWelcome(&selection);

	switch (selection) {

		case 1:
			viewItems(items, 0);
			break;

		case 2:
			promptCreateItem(items);
			break;

		case 0:
			printf("Exiting application. Goodbye!\n");
			exit(1);
			break;

		default:
			printf("Invalid selection. Please try again.\n");
			welcome(items);
			break;
	}
}
