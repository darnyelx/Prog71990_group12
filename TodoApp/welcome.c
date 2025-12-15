#include <stdio.h>
#include "welcome.h"
#include "promptWelcome.h"
#include "ViewItems.h"
#include "Item.h"
#include "promptCreateItem.h"

void welcome(ItemList* items) {
	int selection = 0;
	//clear input buffer
	promptWelcome(&selection);

	switch (selection) {
	case 1:
	{
		viewItems(items, 0);
	
	break;
	}
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
