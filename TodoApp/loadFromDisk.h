#pragma once
#include "Item.h"
ItemList* loadFromDisk();
void freeItems( ItemList* items);
void freeItem( Item* item);