#include <stdio.h>

/*
 * Prompts the user to confirm deletion of an item.
 *
 * Parameters:
 *   selection - pointer to an integer where the user's choice is stored
 *               (1 = Yes, 2 = No)
 *
 * Returns:
 *   None (writes the result to *selection)
 *
 * Author: Junior Felix
 */
void promptDeleteItem(int* selection)
{
	int input;

	while (1) {
		printf("\n=================================\n");
		printf("        DELETE Todo CONFIRMATION \n");
		printf("=================================\n");
		printf("Are you sure you want to delete this Todo?\n");
		printf("---------------------------------\n");
		printf("1. Yes\n");
		printf("2. No\n");
		printf("---------------------------------\n");
		printf("Your choice (1-2): ");

		/* Read user input */
		if (scanf_s("%d", &input) != 1) {
			/* Clear invalid input */
			while (getchar() != '\n');
			printf("Invalid input. Please enter a number.\n");
			continue;
		}

		/* Validate menu range */
		if (input < 1 || input > 2) {
			printf("Invalid choice. Please select a valid option.\n");
			continue;
		}

		*selection = input;
		break;
	}
}
