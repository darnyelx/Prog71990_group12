#include <stdio.h>
#include <string.h>

void promptSearchTerm(char* searchTerm) {

    printf("\n=================================\n");
    printf("              SEARCH             \n");
    printf("=================================\n");

    // Clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // discard characters
    }

    printf("Enter search term: ");
    scanf_s("%99s", searchTerm, 100);
}
