
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "saveToDisk.h"
#include "welcome.h"


void promptCreateItem(ItemList* items) {
    if (items == NULL) {
        printf("Error: Items list is not initialized.\n");
        return;
    }
    
    printf("\n=================================\n");
    printf("        CREATE NEW ITEM\n");
    printf("=================================\n");
    
    // Clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    // Get title
    char title[MAX_TITLE_LENGTH];
    printf("Enter title: ");
    if (fgets(title, MAX_TITLE_LENGTH, stdin) != NULL) {
        // Remove newline character
        title[strcspn(title, "\n")] = '\0';
    } else {
        printf("Error reading title.\n");
        return;
    }
    
    // Get details
    char details[MAX_DETAILS_LENGTH];
    printf("Enter details: ");
    if (fgets(details, MAX_DETAILS_LENGTH, stdin) != NULL) {
        details[strcspn(details, "\n")] = '\0';
    } else {
        printf("Error reading details.\n");
        return;
    }
    
    // Get status
    char status[MAX_STATUS_LENGTH];
    printf("Enter status (Pending/In Progress/Completed): ");
    if (fgets(status, MAX_STATUS_LENGTH, stdin) != NULL) {
        status[strcspn(status, "\n")] = '\0';
        
        // Validate status
        if (strlen(status) == 0) {
            strcpy_s(status, MAX_STATUS_LENGTH, "Pending");
        }
    } else {
        strcpy_s(status, MAX_STATUS_LENGTH, "Pending");
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
	//call welcome again
	//clear input buffer
    welcome(items);
}
