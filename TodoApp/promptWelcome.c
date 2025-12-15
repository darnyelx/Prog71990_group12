#include <stdio.h>

/*
 * Displays the main menu and captures the user's selection.
 *
 * Parameters:
 *   selection - pointer to an integer where the user's choice is stored
 *
 * The function validates input and keeps prompting until a valid option is entered.
 */
void promptWelcome(int* selection)
{
    int input;

    while (1)
    {
        printf("\n=================================\n");
        printf("        TODO APPLICATION\n");
        printf("=================================\n");
        printf("1. View all items\n");
        printf("2. Create a new item\n");
        printf("0. Exit\n");
        printf("---------------------------------\n");
        printf("Enter your choice: ");

        /* Read user input */

        if (scanf("%d", &input) != 1)
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
