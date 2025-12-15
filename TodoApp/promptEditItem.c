#include <stdio.h>
#include <string.h>
#include "Item.h"

void promptEditItem(ItemList* items) {
    if (items == NULL || items->count == 0) {
        printf("Error: No items available to edit.\n");
        return;
    }

    printf("\n=================================\n");
    printf("          EDIT ITEM\n");
    printf("=================================\n");

    // Clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Ask for item ID
    int id;
    printf("Enter the ID of the item to edit: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID input.\n");
        return;
    }

    // Clear input buffer again after scanf
    while ((c = getchar()) != '\n' && c != EOF);

    // Find item
    Item* item = findItemById(items, id);
    if (item == NULL) {
        printf("Error: Item with ID %d not found.\n", id);
        return;
    }

    printf("\nEditing Item ID: %d\n", item->id);
    printf("Leave a field empty to keep the current value.\n\n");

    // Edit title
    char title[MAX_TITLE_LENGTH];
    printf("Current title: %s\nNew title: ", item->title);
    if (fgets(title, MAX_TITLE_LENGTH, stdin)) {
        title[strcspn(title, "\n")] = '\0';
        if (strlen(title) > 0) {
            strncpy(item->title, title, MAX_TITLE_LENGTH - 1);
            item->title[MAX_TITLE_LENGTH - 1] = '\0';
        }
    }

    // Edit details
    char details[MAX_DETAILS_LENGTH];
    printf("Current details: %s\nNew details: ", item->details);
    if (fgets(details, MAX_DETAILS_LENGTH, stdin)) {
        details[strcspn(details, "\n")] = '\0';
        if (strlen(details) > 0) {
            strncpy(item->details, details, MAX_DETAILS_LENGTH - 1);
            item->details[MAX_DETAILS_LENGTH - 1] = '\0';
        }
