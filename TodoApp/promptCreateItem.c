#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "saveToDisk.h"
#include "welcome.h"

/*
 * Clears any remaining characters from the input buffer.
 * This is used after scanf/scanf_s to remove leftover newline characters.
 */
static void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/*
 * Prompts the user to create a new Todo item and adds it to the list.
 *
 * Parameters:
 *   items - pointer to the ItemList where the new item will be stored
 *
 * Behavior:
 *   - Collects title and details using fgets (supports spaces)
 *   - Lets the user choose a status using a numeric menu
 *   - Generates a new ID, creates the item, validates it, and adds it to the list
 *   - Saves the updated list to disk, then returns to the main menu
 *
 * Notes:
 *   - Uses fgets for text input to avoid input-buffer issues
 *   - Uses scanf_s only for numeric status selection (then clears buffer)
 *
 * Author: Junior Felix
 */
void promptCreateItem(ItemList* items)
{
    clearScreen();

    // Validate list pointer
    if (items == NULL) {
        printf("Error: Todo list is not initialized.\n");
        return;
    }

    // Screen title
    printf("\n=================================\n");
    printf("          CREATE NEW TODO        \n");
    printf("=================================\n");

    // Get title (use fgets to allow spaces)
    char title[MAX_TITLE_LENGTH];
    printf("Enter title: ");
    fflush(stdout);
	while (getchar() != '\n');  // clear input buffer
    if (fgets(title, MAX_TITLE_LENGTH, stdin) != NULL) {
        title[strcspn(title, "\r\n")] = '\0';  // trim newline
    } else {
        printf("Error reading title.\n");
        return;
    }

    // Get details (use fgets to allow spaces)
    char details[MAX_DETAILS_LENGTH];
    printf("Enter details: ");
    fflush(stdout);

    if (fgets(details, MAX_DETAILS_LENGTH, stdin) != NULL) {
        details[strcspn(details, "\r\n")] = '\0';  // trim newline
    } else {
        printf("Error reading details.\n");
        return;
    }

    // Status selection (numeric input)
    int statusChoice = -1;
    char status[MAX_STATUS_LENGTH];

    printf("\nSelect status:\n");
    printf("1) Pending\n");
    printf("2) In Progress\n");
    printf("3) Completed\n");

    // Loop until a valid menu option is entered
    while (1) {
        printf("Your choice (1-3): ");
        fflush(stdout);

        if (scanf_s("%d", &statusChoice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number (1-3).\n");
            continue;
        }

        // Remove leftover newline after scanf_s
        clearInputBuffer();

        if (statusChoice < 1 || statusChoice > 3) {
            printf("Invalid option. Please choose 1, 2, or 3.\n");
            continue;
        }

        break;
    }

    // Convert the numeric choice into a status string
    switch (statusChoice) {
        case 1: strcpy_s(status, MAX_STATUS_LENGTH, "Pending"); break;
        case 2: strcpy_s(status, MAX_STATUS_LENGTH, "In Progress"); break;
        case 3: strcpy_s(status, MAX_STATUS_LENGTH, "Completed"); break;
        default: strcpy_s(status, MAX_STATUS_LENGTH, "Pending"); break;
    }

    // Generate new ID (simple approach: count + 1)
    int newId = (int)(items->count + 1);

    // Build the item using your factory function
    Item newItem = createItem(newId, title, details, status);

    // Validate required fields before adding
    if (!validateItem(&newItem)) {
        printf("Error: Invalid item data.\n");
        return;
    }

    // Add new item to the list
    if (!addItem(items, &newItem)) {
        printf("Error: Failed to add item to list.\n");
        return;
    }

    // Persist changes
    saveToDisk(items);

    printf("\nItem created successfully with ID: %d\n", newId);

    // Return to main menu
    welcome(items);
}
