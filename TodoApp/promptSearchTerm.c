#include <stdio.h>
#include <string.h>

void promptSearchTerm(char* searchTerm) {
	// Clear input buffer
	while (getchar() != '\n');
	printf("Enter search term: ");
	scanf_s("%99[^\n]", searchTerm,99);

	size_t len = strlen(searchTerm);
	if (len > 0 && searchTerm[len - 1] == '\n') {
		searchTerm[len - 1] = '\0';
	}
}