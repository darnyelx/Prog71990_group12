#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Item.h"
#include "saveToDisk.h"

#define CSV_FILE "./todo_list.csv"

/*
 * Writes a CSV field to the file.
 *
 * Behavior:
 *   - Always wraps the field in double quotes
 *   - Ignores any double quotes found in the original string
 *
 * Parameters:
 *   fp - file pointer to write to
 *   s  - field value to write
 */
static void writeCsvField(FILE* fp, const char* s)
{
    if (!s) s = "";

    // Open quote
    fputc('"', fp);

    // Write characters, ignoring quote characters
    for (const char* p = s; *p; p++) {
        if (*p == '"') {
            continue;
        }
        fputc(*p, fp);
    }

    // Close quote
    fputc('"', fp);
}

/*
 * Saves the current ItemList to disk as a CSV file.
 *
 * Parameters:
 *   items - pointer to the ItemList to be saved
 *
 * Behavior:
 *   - Overwrites the existing CSV file
 *   - Writes a header row followed by one row per item
 *   - Uses quoted fields for consistent CSV formatting
 *
 * Notes:
 *   - The CSV column order must match loadFromDisk()
 *
 * Author: Ifeanyi Chiemeke
 */
void saveToDisk(ItemList* items)
{
    // Validate items list pointer
    if (!items) return;

    FILE* fp = fopen(CSV_FILE, "w");
    if (!fp) {
        printf("Error: could not open %s for writing\n", CSV_FILE);
        return;
    }

    fprintf(fp, "id,title,details,created,status\n");

    // Write each item as a CSV row
    for (size_t i = 0; i < items->count; i++)
    {
        Item* it = &items->data[i];

        // ID is numeric, so it can be written without quotes
        fprintf(fp, "%d,", it->id);

        // Write remaining fields as quoted CSV fields
        writeCsvField(fp, it->title);
        fputc(',', fp);

        writeCsvField(fp, it->details);
        fputc(',', fp);

        writeCsvField(fp, it->created);
        fputc(',', fp);

        writeCsvField(fp, it->status);

        fputc('\n', fp);
    }

    fclose(fp);
}
