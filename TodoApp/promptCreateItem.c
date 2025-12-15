#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "saveToDisk.h"
#include "welcome.h"

static void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void promptCreateItem(ItemList* items)
{
    clearScreen();
    if (items == NULL) {
        printf("Error: Todo list is not initialized.\n");
        return;
    }

    printf("\n=================================\n");
    printf("        CREATE NEW Todo\n");
    printf("=================================\n");

    // Clear input buffer (only needed if previous input used scanf/scanf_s)
    clearInputBuffer();

    // Get title
    char title[MAX_TITLE_LENGTH];
    printf("Enter title: ");
    fflush(stdout);
    if (fgets(title, MAX_TITLE_LENGTH, stdin) != NULL) {
        title[strcspn(title, "\r\n")] = '\0';
    }
    else {
        printf("Error reading title.\n");
        return;
    }

    // Get details
    char details[MAX_DETAILS_LENGTH];
    printf("Enter details: ");
    fflush(stdout);
    if (fgets(details, MAX_DETAILS_LENGTH, stdin) != NULL) {
        details[strcspn(details, "\r\n")] = '\0';
    }
    else {
        printf("Error reading details.\n");
        return;
    }

    // Status selection (numbers)
    int statusChoice = -1;
    char status[MAX_STATUS_LENGTH];

    printf("\nSelect status:\n");
    printf("1) Pending\n");
    printf("2) In Progress\n");
    printf("3) Completed\n");

    while (1) {
        printf("Your choice (1-3): ");
        fflush(stdout);

        if (scanf_s("%d", &statusChoice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number (1-3).\n");
            continue;
        }

        clearInputBuffer();

        if (statusChoice < 1 || statusChoice > 3) {
            printf("Invalid option. Please choose 1, 2, or 3.\n");
            continue;
        }

        break;
    }

    switch (statusChoice) {
    case 1: strcpy_s(status, MAX_STATUS_LENGTH, "Pending"); break;
    case 2: strcpy_s(status, MAX_STATUS_LENGTH, "In Progress"); break;
    case 3: strcpy_s(status, MAX_STATUS_LENGTH, "Completed"); break;
    default: strcpy_s(status, MAX_STATUS_LENGTH, "Pending"); break; // safety
    }

    // Generate new ID (simple approach - use current count + 1)
    int newId = (int)(items->count + 1);

    // Create the item
    Item newItem = createItem(newId, title, details, status);

    // Validate the item
    if (!validateItem(&newItem)) {
        printf("Error: Invalid item data.\n");
        return;
    }

    // Add to list
    if (!addItem(items, &newItem)) {
        printf("Error: Failed to add item to list.\n");
        return;
    }

    // Save immediately
    saveToDisk(items);

    printf("\nItem created successfully with ID: %d\n", newId);

    // Return to main menu
    welcome(items);
}
