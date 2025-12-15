#include <stdio.h>
#include "Item.h"

#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10
#define CSV_COLS 6

#define CSV_COLS 6
#define FIELD_MAX 500

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
            // cleanup if partial alloc failed
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

            if (col >= CSV_COLS) break; // too many columns
        }
        else {
            if (pos < FIELD_MAX - 1) {
                arrayOfWords[col][pos++] = c;
            }
        }

        charIndex++;
    }

    if (col < CSV_COLS)
        arrayOfWords[col][pos] = '\0';

    return arrayOfWords;
}




ItemList* loadFromDisk(void)
{
    FILE* filePtr = fopen("./Item_list.csv", "r");
    if (!filePtr) {
        printf("Error opening file\n");
        return NULL;
    }

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

    // Skip header
    fgets(line, sizeof(line), filePtr);

    while (fgets(line, sizeof(line), filePtr))
    {
        char** parsedLine = parseCsvLine(line);
        if (!parsedLine) continue;

        // grow array if needed
        if (list->count == list->capacity) {
            list->capacity *= 2;
            Item* temp = realloc(list->data, sizeof(Item) * list->capacity);
            if (!temp) {
                fclose(filePtr);
                free(list->data);
                free(list);
                return NULL;
            }
            list->data = temp;
        }

        Item* t = &list->data[list->count];

        t->id = atoi(parsedLine[0]);

        strncpy_s(t->title, sizeof(t->title), parsedLine[1], _TRUNCATE);
        strncpy_s(t->details, sizeof(t->details), parsedLine[2], _TRUNCATE);
        strncpy_s(t->created, sizeof(t->created), parsedLine[3], _TRUNCATE);
        strncpy_s(t->status, sizeof(t->status), parsedLine[5], _TRUNCATE);


        t->title[sizeof(t->title) - 1] = '\0';
        t->details[sizeof(t->details) - 1] = '\0';
        t->created[sizeof(t->created) - 1] = '\0';
        t->status[sizeof(t->status) - 1] = '\0';

        list->count++;

        for (int i = 0; i < CSV_COLS; i++) free(parsedLine[i]);
        free(parsedLine);
    }

    fclose(filePtr);
    return list;
}
