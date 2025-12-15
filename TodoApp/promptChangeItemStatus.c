#include <stdio.h>
#include <string.h>
#include "Item.h"

#define MAX_STATUS_LENGTH 20

static void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void promptChangeItemStatus(Item* item)
{
    if (item == NULL) {
        printf("Error: Invalid Todo.\n");
        return;
    }

    int selection = -1;

    printf("\n=================================\n");
    printf("         CHANGE Todo STATUS      \n");
    printf("=================================\n");
    printf("Item   : %s\n", item->title);
    printf("Current: %s\n", item->status);
    printf("---------------------------------\n");
    printf("1) Pending\n");
    printf("2) In Progress\n");
    printf("3) Completed\n");
    printf("0) Cancel\n");
    printf("---------------------------------\n");

    while (1) {
        printf("Select status (0-3): ");
        fflush(stdout);

        if (scanf_s("%d", &selection) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number (0-3).\n");
            continue;
        }

        clearInputBuffer();

        if (selection < 0 || selection > 3) {
            printf("Invalid option. Please choose between 0 and 3.\n");
            continue;
        }

        break;
    }

    if (selection == 0) {
        printf("Status change cancelled.\n");
        return;
    }

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
        // should never happen due to validation
        strcpy_s(item->status, MAX_STATUS_LENGTH, "Pending");
        break;
    }

    printf("Status updated successfully: %s\n", item->status);
}
