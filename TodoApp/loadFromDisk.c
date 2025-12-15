#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

#define INITIAL_CAPACITY 10
#define CSV_COLS 6
#define FIELD_MAX 500

/*
 * Splits one CSV line into CSV_COLS fields.
 * Supports commas inside quotes. Quotes are ignored (not stored).
 * Returns an allocated array of strings; caller must free each field and the array.
 * Author: "Ifeanyi Chiemeke"
 */
char** parseCsvLine(const char* line)
{
    int charIndex = 0;
    int isQuoteOpen = 0;
    int col = 0;
    int pos = 0;

    char** arrayOfWords = malloc(sizeof(char*) * CSV_COLS);
    if (!arrayOfWords) return NULL;

    for (int i = 0; i < CSV_COLS; i++) {
        arrayOfWords[i] = malloc(FIELD_MAX);
        if (!arrayOfWords[i]) {
            for (int j = 0; j < i; j++) free(arrayOfWords[j]);
            free(arrayOfWords);
            return NULL;
        }
        arrayOfWords[i][0] = '\0';
    }

    while (line[charIndex] != '\0' && line[charIndex] != '\n' && line[charIndex] != '\r')
    {
        char c = line[charIndex];

        if (c == '"') {
            isQuoteOpen = !isQuoteOpen;
        }
        else if (c == ',' && !isQuoteOpen) {
            arrayOfWords[col][pos] = '\0';
            col++;
            pos = 0;

            if (col >= CSV_COLS) {
                break;  // too many columns in input line
            }
        }
        else {
            if (pos < FIELD_MAX - 1) {
                arrayOfWords[col][pos++] = c;
            }
        }

        charIndex++;
    }

    if (col < CSV_COLS) {
        arrayOfWords[col][pos] = '\0';
    }

    return arrayOfWords;
}

/*
 * Loads items from ./todo_list.csv into a dynamically allocated ItemList.
 * If the file does not exist, it is created and initialized with a header row.
 *  Author: "Ifeanyi Chiemeke"
 */
ItemList* loadFromDisk(void)
{
    FILE* filePtr = NULL;

    // Try open for reading
    fopen_s(&filePtr, "./todo_list.csv", "r");

    // If it doesn't exist, create it and write header
    if (!filePtr) {
        fopen_s(&filePtr, "./todo_list.csv", "w+");
        if (!filePtr) {
            printf("Error creating file\n");
            return NULL;
        }

        fprintf(filePtr, "id,title,details,created,status,updated\n");
        fflush(filePtr);
        rewind(filePtr);
    }

    printf("Loading items from disk...\n");

    ItemList* list = malloc(sizeof(ItemList));
    if (!list) {
        fclose(filePtr);
        return NULL;
    }

    list->count = 0;
    list->capacity = INITIAL_CAPACITY;
    list->data = malloc(sizeof(Item) * list->capacity);

    if (!list->data) {
        fclose(filePtr);
        free(list);
        return NULL;
    }

    char line[1000];

    // Skip header if present
    if (!fgets(line, sizeof(line), filePtr)) {
        fclose(filePtr);
        return list; // empty file, return empty list
    }

    while (fgets(line, sizeof(line), filePtr))
    {
        char** parsedLine = parseCsvLine(line);
        if (!parsedLine) continue;

        // grow array if it's needed
        if (list->count == list->capacity) {
            list->capacity *= 2;
            Item* temp = realloc(list->data, sizeof(Item) * list->capacity);
            if (!temp) {
                for (int i = 0; i < CSV_COLS; i++) free(parsedLine[i]);
                free(parsedLine);

                fclose(filePtr);
                free(list->data);
                free(list);
                return NULL;
            }
            list->data = temp;
        }

        Item* t = &list->data[list->count];

        // Map CSV columns -> struct fields
        t->id = atoi(parsedLine[0]);

        strncpy_s(t->title, sizeof(t->title), parsedLine[1], _TRUNCATE);
        strncpy_s(t->details, sizeof(t->details), parsedLine[2], _TRUNCATE);
        strncpy_s(t->created, sizeof(t->created), parsedLine[3], _TRUNCATE);
        strncpy_s(t->status, sizeof(t->status), parsedLine[4], _TRUNCATE);

        list->count++;

        for (int i = 0; i < CSV_COLS; i++) free(parsedLine[i]);
        free(parsedLine);
    }

    fclose(filePtr);
    return list;
}
