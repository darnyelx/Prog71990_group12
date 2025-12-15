#include <stdio.h>
#include <string.h>
#include "Item.h"
#include "getItemById.h"

void promptEditItem(Item* item) {
    clearScreen();

    printf("\n=================================\n");
    printf("          EDIT Todo\n");
    printf("=================================\n");

    // Clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Ask for item ID
  

    // Clear input buffer again after scanf
    //while ((c = getchar()) != '\n' && c != EOF);
  
    printf("\n Editing Item ID: %d\n", item->id);
    printf(" Leave a field empty to keep the current value.\n\n");

    // Edit title
    char title[MAX_TITLE_LENGTH];
    printf("Current title: %s\nNew title: ", item->title);
    if (fgets(title, MAX_TITLE_LENGTH, stdin)) {
        title[strcspn(title, "\n")] = '\0';
        if (strlen(title) > 0) {
            strncpy_s(item->title, MAX_TITLE_LENGTH, title, _TRUNCATE);
        }
    }

    // Edit details
    char details[MAX_DETAILS_LENGTH];
    printf("Current details: %s\nNew details: ", item->details);
    if (fgets(details, MAX_DETAILS_LENGTH, stdin)) {
        details[strcspn(details, "\n")] = '\0';
        if (strlen(details) > 0) {
            strncpy_s(item->details, MAX_DETAILS_LENGTH, details, _TRUNCATE);
            item->details[MAX_DETAILS_LENGTH - 1] = '\0';
        }
    }
}