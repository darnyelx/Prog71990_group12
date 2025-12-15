#include <stdio.h>

void promptSingleItemAction(int* selection)
{
	int input;
	while (1)
	{
		printf("\n---------------------------------\n");
		printf("       ITEM ACTION MENU\n");
		printf("---------------------------------\n");
		printf("1. Edit item\n");
		printf("2. Delete item\n");
		printf("3. Change item status\n");
		printf("0. Back to all items\n");
		printf("---------------------------------\n");
		printf("Enter your choice: ");
		/* Read user input */
		if (scanf_s("%d", &input) != 1)
		{
			/* Clear invalid input */
			while (getchar() != '\n');
			printf("Invalid input. Please enter a number.\n");
			continue;
		}
		/* Validate menu range */
		if (input < 0 || input > 3)
		{
			printf("Invalid choice. Please select a valid option.\n");
			continue;
		}
		*selection = input;
		break;
	}
}