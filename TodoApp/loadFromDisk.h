#pragma once
#include "Item.h"
struct Item** loadFromDisk();
void freeItems( ItemList* items);
void freeItem( Item* item);