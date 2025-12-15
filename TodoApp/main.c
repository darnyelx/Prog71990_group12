
#include <stdio.h>
#include "promptWelcome.h"
#include "ViewItems.h";
#include "loadFromDisk.h"
#include "Item.h";
#include "promptCreateItem.h"

void welcome() {
	int selection = 0;
	promptWelcome(&selection);
	Item** items = loadFromDisk();

	switch (selection) {
	case 1:
	{
		viewItems(items);
	}
	case 2:
		 promptCreateItem(items);
		break;
	case 0:
		exit(1);
		break;

	default:
		printf("Invalid selection. Please try again.\n");
		welcome();
		break;

	}
}

int main() {
	welcome();
}