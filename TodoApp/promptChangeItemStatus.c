#include <stdio.h>
#include <string.h>
#include "Item.h"

#define MAX_STATUS_LENGTH 20

/*
 * Clears any remaining characters from the input buffer.
 * This prevents invalid input from affecting subsequent reads.
 */
static void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/*
 * Prompts the user to change the status of an existing item.
 *
 * Parameters:
 *   item - pointer to the Item whose status will be updated
 *
 * Behavior:
 *   - Displays a menu of predefined status options
 *   - Allows the user to select a status using a number
 *   - Updates the item's status based on the selection
 *
 * Notes:
 *   - Selecting 0 cancels the operation without making changes
 *   - Input is validated to ensure a valid option is chosen
 *
 * Author: Junior Felix
 */
void promptChangeItemStatus(Item* item)
{
    // Validate the item pointer
    if (item == NULL) {
        printf("Error: Invalid Todo.\n");
        return;
    }

    int selection = -1;

    // Display status selection menu
    printf("\n=================================\n");
    printf("         CHANGE Todo STATUS      \n");
    printf("=================================\n");
    printf("Todo title   : %s\n", item->title);
    printf("Current: %s\n", item->status);
    printf("---------------------------------\n");
    printf("1) Pending\n");
    printf("2) In Progress\n");
    printf("3) Completed\n");
    printf("0) Cancel\n");
    printf("---------------------------------\n");

    // Continuously prompt until valid input is received
    while (1) {
        printf("Select status (0-3): ");
        fflush(stdout);

        // Read numeric input and validate
        if (scanf_s("%d", &selection) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number (0-3).\n");
            continue;
        }

        // Clear any extra input characters
        clearInputBuffer();

        // Validate range
        if (selection < 0 || selection > 3) {
            printf("Invalid option. Please choose between 0 and 3.\n");
            continue;
        }

        break;
    }

    // Handle cancel option
    if (selection == 0) {
        printf("Status change cancelled.\n");
        return;
    }

    // Update status based on user selection
    switch (selection) {
        case 1:
            strcpy_s(item->status, MAX_STATUS_LENGTH, "Pending");
            break;
        case 2:
            strcpy_s(item->status, MAX_STATUS_LENGTH, "In Progress");
            break;
        case 3:
            strcpy_s(item->status, MAX_STATUS_LENGTH, "Completed");
            break;
        default:
            // Fallback (should not occur due to validation)
            strcpy_s(item->status, MAX_STATUS_LENGTH, "Pending");
            break;
    }

    // Confirm successful update
    printf("Status updated successfully: %s\n", item->status);
}
