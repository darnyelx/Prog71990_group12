#include <stdio.h>

void promptDeleteItem(int* selection) {
	int input;
	while (1) {
		printf("\nAre you sure you want to delete this item?\n");
		printf("1. Yes\n");
		printf("2. No\n");
		printf("Enter your choice: ");
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
