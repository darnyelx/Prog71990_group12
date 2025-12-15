#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Item.h"
#include "saveToDisk.h"

#define CSV_FILE "./todo_list.csv"

// Writes a CSV-safe field:
// - wraps in quotes if it contains comma, quote, or newline
// - escapes quotes by doubling them: " -> ""
static void writeCsvField(FILE* fp, const char* s)
{
    if (!s) s = "";

    int needsQuotes = 0;
    for (const char* p = s; *p; p++) {
        if (*p == ',' || *p == '"' || *p == '\n' || *p == '\r') {
            needsQuotes = 1;
            break;
        }
    }

    if (!needsQuotes) {
        fputs(s, fp);
        return;
    }

    fputc('"', fp);
    for (const char* p = s; *p; p++) {
        if (*p == '"') fputc('"', fp);  // escape quote
        fputc(*p, fp);
    }
    fputc('"', fp);
}

void saveToDisk(ItemList* items)
{
    if (!items) return;

    FILE* fp = fopen(CSV_FILE, "w");
    if (!fp) {
        printf("Error: could not open %s for writing\n", CSV_FILE);
        return;
    }

    // Header row (match your readCSV columns)
    fprintf(fp, "id,title,items,created,updated,status\n");

    for (size_t i = 0; i < items->count; i++)
    {
        Item* it = &items->data[i];

        fprintf(fp, "%d,", it->id);

        writeCsvField(fp, it->title);   fputc(',', fp);
        writeCsvField(fp, it->details);   fputc(',', fp);
        writeCsvField(fp, it->created); fputc(',', fp);
        writeCsvField(fp, it->status);

        fputc('\n', fp);
    }

    fclose(fp);
}
