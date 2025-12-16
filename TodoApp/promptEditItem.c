#include <stdio.h>
#include <string.h>
#include "Item.h"
#include "getItemById.h"

/*
 * Prompts the user to edit an existing Todo item.
 *
 * Parameters:
 *   item - pointer to the Item that will be edited
 *
 * Behavior:
 *   - Displays the current item information
 *   - Prompts for a new title and new details
 *   - If the user enters an empty line, the current value is kept
 *
 * Notes:
 *   - Uses fgets to support spaces in input
 *   - Input buffer is cleared before reading to avoid leftover newline issues
 *
 * Author: Kadeema Wakha
 */
void promptEditItem(Item* item)
{
    clearScreen();

    // Validate item pointer
    if (item == NULL) {
        printf("Error: Invalid item.\n");
        return;
    }

    // Screen title
    printf("\n=================================\n");
    printf("             EDIT TODO           \n");
    printf("=================================\n");

    // Clear input buffer (useful if the previous step used scanf/scanf_s)
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    // Show context for the user
    printf("\nEditing Item ID: %d\n", item->id);
    printf("Leave a field empty to keep the current value.\n\n");

    // ---- Edit Title ----
    char title[MAX_TITLE_LENGTH];

    printf("Current title: %s\n", item->title);
    printf("New title: ");

    if (fgets(title, MAX_TITLE_LENGTH, stdin)) {
        // Remove trailing newline from input
        title[strcspn(title, "\n")] = '\0';

        // Only update if user typed something
        if (strlen(title) > 0) {
            strncpy_s(item->title, MAX_TITLE_LENGTH, title, _TRUNCATE);
        }
    }

    // ---- Edit Details ----
    char details[MAX_DETAILS_LENGTH];

    printf("\nCurrent details: %s\n", item->details);
    printf("New details: ");

    if (fgets(details, MAX_DETAILS_LENGTH, stdin)) {
        // Remove trailing newline from input
        details[strcspn(details, "\n")] = '\0';

        // Only update if user typed something
        if (strlen(details) > 0) {
            strncpy_s(item->details, MAX_DETAILS_LENGTH, details, _TRUNCATE);
            item->details[MAX_DETAILS_LENGTH - 1] = '\0';
        }
    }
}
