#include <stdio.h>

/*
 * Displays the main menu and captures the user's selection.
 *
 * Parameters:
 *   selection - pointer to an integer where the user's choice is stored
 *
 * Behavior:
 *   - Displays the main application menu
 *   - Prompts the user to select an option
 *   - Repeats until valid numeric input is entered
 *
 * Author: Kadeema Wakha
 */
void promptWelcome(int* selection)
{
    int input;

    while (1)
    {
        // Display main menu
        printf("\n=================================\n");
        printf("         TODO APPLICATION        \n");
        printf("=================================\n");
        printf("1) View all Todos\n");
        printf("2) Create a new Todo\n");
        printf("0) Exit\n");
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
