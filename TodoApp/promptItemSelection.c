#include <stdio.h>

/*
 * Prompts the user to select an item action or item ID.
 *
 * Parameters:
 *   selection - pointer to an integer where the user's input is stored
 *
 * Behavior:
 *   - Allows the user to enter an item ID to view details
 *   - Accepts special options:
 *       -1 -> search items
 *        0 -> return to the main menu
 *   - Repeats until valid numeric input is provided
 *
 * Notes:
 *   - Input is validated to prevent non-numeric entries
 *
 * Author: Ifeanyi Chiemeke
 */
void promptItemSelection(int* selection)
{
	int input;

	// Continue prompting until valid input is received
	while (1)
	{
		// Display menu
		printf("\n=====================================\n");
		printf("|           Todo SELECTION           |\n");
		printf("=====================================\n");
		printf("| Enter a Todo ID to view details   |\n");
		printf("|                                   |\n");
		printf("|  -1  -> Search items               |\n");
		printf("|   0  -> Return to main menu        |\n");
		printf("-------------------------------------\n");
		printf("Your choice: ");

		/* Read user input */
		if (scanf_s("%d", &input) != 1)
		{
			/* Clear invalid input from buffer */
			while (getchar() != '\n') { }
			printf("  Invalid input. Please enter a number.\n");
			continue;
		}

		/* Validate input range */
		if (input < -1)
		{
			printf("  Invalid choice. Please select a valid option.\n");
			continue;
		}

		// Store valid selection and exit loop
		*selection = input;
		break;
	}
}
