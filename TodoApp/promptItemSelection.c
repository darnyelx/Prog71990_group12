#include <stdio.h>

void promptItemSelection(int* selection)
{
	int input;
	while (1)
	{
		printf("\n=====================================\n");
		printf("|           ITEM SELECTION           |\n");
		printf("=====================================\n");
		printf("| Enter an Item ID to view details   |\n");
		printf("|                                   |\n");
		printf("|  -1  -> Search items               |\n");
		printf("|   0  -> Return to main menu        |\n");
		printf("-------------------------------------\n");
		printf("Your choice: ");


		/* Read user input */

                if (scanf_s("%d", &input) != 1)
		{
			/* Clear invalid input */
			while (getchar() != '\n');
			printf("  Invalid input. Please enter a number.\n");
			continue;
		}
		/* Validate input */
		if (input < -1)
		{
			printf("  Invalid choice. Please select a valid option.\n");
			continue;
		}
		*selection = input;
		break;
	}
}