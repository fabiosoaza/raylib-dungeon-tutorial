#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"

#define ARRAY_SIZE(array) sizeof(array) * sizeof(array[0])

typedef struct _IntMatrix
{
    int rows;
    int cols;
    int *data;
} IntMatrix;

IntMatrix LoadIntMatrixFromFile(const char *filename, const char *delimiter)
{
    IntMatrix data = {.rows = 0, .cols = 0, .data = NULL};

    FILE *file = fopen(filename, "rt");

    if (file == NULL)
    {
        printf("Error opening file %s.\n", filename);
        return data;
    }

    int counter = 0;
    int temp = 0;
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL)
    {

        char *token = strtok(line, delimiter);
        while (token != NULL)
        {
            // Utiliza sscanf para analisar os inteiros da linha
            if (sscanf(token, "%d", &temp) == 1)
            {
                counter++;
            }
            token = strtok(NULL, delimiter);
        }
    }

    if (counter == 0)
    {
        fclose(file);
        printf("File  %s is empty.\n", filename);
        return data;
    }

    data.data = (int *)calloc(counter, sizeof(int));

    if (data.data == NULL)
    {
        fclose(file);
        printf("Memory could not be allocated .\n");
        return data;
    }

    temp = 0;
    rewind(file);
    int index = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *token = strtok(line, delimiter);
        while (token != NULL)
        {
            // Utiliza sscanf para analisar os inteiros da linha
            if (sscanf(token, "%d", &temp) == 1)
            {
                data.data[index++] = temp;
                if (data.rows == 0)
                {
                    data.cols++;
                }
            }
            token = strtok(NULL, delimiter);
        }
        data.rows++;
    }

    fclose(file);

    return data;
}