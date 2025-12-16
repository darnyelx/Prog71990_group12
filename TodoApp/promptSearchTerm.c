#include <stdio.h>
#include <string.h>

/*
 * Prompts the user to enter a search term for filtering Todos.
 *
 * Parameters:
 *   searchTerm - character buffer where the entered search term is stored
 *
 * Behavior:
 *   - Displays a search header
 *   - Clears any leftover input from previous reads
 *   - Reads a single-word search term from standard input
 *
 * Notes:
 *   - Uses scanf_s, so spaces are not allowed in the search term
 *   - Buffer size is limited to prevent overflow
 *
 * Author: Ifeanyi Chiemeke
 */
void promptSearchTerm(char* searchTerm)
{
    // Display search header
    printf("\n=================================\n");
    printf("           SEARCH TODOS           \n");
    printf("=================================\n");

    // Clear input buffer to remove leftover characters
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // discard characters
    }

    // Prompt user for search keyword
    printf("Enter search term: ");
    scanf_s("%99s", searchTerm, 100);
}
