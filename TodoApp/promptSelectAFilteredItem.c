#include <stdio.h>

void promptSelectAFilteredItem(int* selection)
{
	int input;
	while (1)
	{
		printf("\n---------------------------------\n");
		printf("Select an item by its ID to view details.\n");
		printf("Enter 0 to return to all Task.\n");
		printf("---------------------------------\n");
		printf("Your choice: ");
		/* Read user input */
		if (scanf_s("%d", &input) != 1)
		{
			/* Clear invalid input */
			while (getchar() != '\n');
			printf("Invalid input. Please enter a number.\n");
			continue;
		}
		/* Validate input */
		if (input < -1)
		{
			printf("Invalid choice. Please select a valid option.\n");
			continue;
		}
		*selection = input;
		break;
	}
}