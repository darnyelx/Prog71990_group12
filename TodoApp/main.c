
#include <stdio.h>
#include "promptWelcome.h"
#include "ViewItems.h";
#include "loadFromDisk.h"
#include "Item.h";
#include "promptCreateItem.h"
#include "welcome.h"

int main() {
	ItemList* items = loadFromDisk();
	if (items == NULL)
	{
		printf("Failed to load items from disk.\n");
		exit(1);
	}
	welcome(items);
}