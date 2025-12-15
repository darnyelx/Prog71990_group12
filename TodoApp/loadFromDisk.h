#pragma once
struct Item** loadFromDisk();
void freeItems(struct Items** items);
void freeItem(struct Item* item);