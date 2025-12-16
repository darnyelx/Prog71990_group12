#include <stdio.h>

/*
 * Prompts the user to select an action for a single item.
 *
 * Parameters:
 *   selection - pointer to an integer where the user's choice is stored
 *
 * Behavior:
 *   - Displays a menu of actions that can be performed on an item
 *   - Allows the user to edit, delete, change status, or return
 *   - Repeats until a valid numeric option is entered
 *
 * Notes:
 *   - Input is validated to ensure it falls within the allowed range
 *
 * Author: Junior Felix
 */
void promptSingleItemAction(int* selection)
{
	int input;

	while (1)
	{
		// Display action menu
		printf("\n=================================\n");
		printf("        Todo ACTION MENU         \n");
		printf("=================================\n");
		printf("1) Edit Todo\n");
		printf("2) Delete Todo\n");
		printf("3) Change Todo status\n");
		printf("0) Back to all Todos\n");
		printf("---------------------------------\n");
		printf("Enter your choice: ");

		/* Read user input */
		if (scanf_s("%d", &input) != 1)
		{
			/* Clear invalid input */
			while (getchar() != '\n') { }
			printf("Invalid input. Please enter a number.\n");
			continue;
		}

		/* Validate menu range */
		if (input < 0 || input > 3)
		{
			printf("Invalid choice. Please select a valid option.\n");
			continue;
		}

		// Store valid selection and exit loop
		*selection = input;
		break;
	}
}
