#include <stdio.h>

/*
 * Prompts the user to select an item from a filtered list.
 *
 * Parameters:
 *   selection - pointer to an integer where the user's choice is stored
 *
 * Behavior:
 *   - Allows the user to enter an item ID to view details
 *   - Accepts 0 to return to the full list of Todos
 *   - Repeats until valid numeric input is provided
 *
 * Notes:
 *   - Only non-negative numbers are accepted
 *
 * Author: Junior Felix
 */
void promptSelectAFilteredItem(int* selection)
{
	int input;

	while (1)
	{
		// Display selection menu
		printf("\n---------------------------------\n");
		printf("Select a Todo by its ID to view details.\n");
		printf("Enter 0 to return to all TODOs.\n");
		printf("---------------------------------\n");
		printf("Your choice: ");

		/* Read user input */
		if (scanf_s("%d", &input) != 1)
		{
			/* Clear invalid input */
			while (getchar() != '\n') { }
			printf("Invalid input. Please enter a number.\n");
			continue;
		}

		/* Validate input - allow 0 and positive numbers only */
		if (input < 0)
		{
			printf("Invalid choice. Please select a valid option.\n");
			continue;
		}

		// Store valid selection and exit loop
		*selection = input;
		break;
	}
}
