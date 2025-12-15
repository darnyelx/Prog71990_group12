
#include <stdio.h>
#include <string.h>

void promptSearchTerm(char* searchTerm) {
    // Clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("Enter search term: ");
    if (fgets(searchTerm, 100, stdin) != NULL) {
        searchTerm[strcspn(searchTerm, "\n")] = '\0';
    }
}
