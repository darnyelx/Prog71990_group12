
#include <stdio.h>
#include <string.h>
#include "Item.h"
#include "saveToDisk.h"

#define MAX_STATUS_LENGTH 20

void promptChangeItemStatus(Item* item) {
    if (item == NULL) {
        printf("Error: Invalid item.\n");
        return;
    }
    
    printf("\n=================================\n");
    printf("      CHANGE ITEM STATUS\n");
    printf("=================================\n");
    printf("Current item: %s\n", item->title);
    printf("Current status: %s\n", item->status);
    
    // Clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    char newStatus[MAX_STATUS_LENGTH];
    printf("Enter new status (Pending/In Progress/Completed): ");
    if (fgets(newStatus, MAX_STATUS_LENGTH, stdin) != NULL) {
        newStatus[strcspn(newStatus, "\n")] = '\0';
        
        // Validate status
        if (strlen(newStatus) == 0) {
            strcpy(newStatus, "Pending");
        }
    } else {
        strcpy(newStatus, "Pending");
    }
    
    strcpy(item->status, newStatus);
    printf("Status updated successfully.\n");
}
