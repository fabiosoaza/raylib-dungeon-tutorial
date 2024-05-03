

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "tilemap.h"

Tilemap LoadTilemap(const char *valuesMap, const char *collidersMap)
{
    Tilemap map = {0};
    const char *fileExt;

    if ((fileExt = strrchr(valuesMap, '.')) != NULL)
    {
        // Check if file extension is supported
        if (strcmp(fileExt, ".txt") == 0)
        {
            int counter = 0;
            int temp = 0;

            // Read values from text file
            FILE *valuesFile = fopen(valuesMap, "rt");

            // Determine the number of tiles in the map by counting the values in the file
            while (fscanf(valuesFile, "%i", &temp) != EOF)
            {
                counter++;
            }

            // Return to the beginning of the file, to read again
            rewind(valuesFile);

            // Allocate memory for the tiles based on the number of values read
            map.tiles = (Tile *)malloc(counter * sizeof(Tile));

            // Set the tile count in the X and Y directions
            map.tileCountX = 12; // Update with your actual tilemap dimensions
            map.tileCountY = 8;  // Update with your actual tilemap dimensions

            counter = 0;

            // Read values from text file and assign them to the tilemap
            while (counter < map.tileCountX * map.tileCountY && fscanf(valuesFile, "%i", &map.tiles[counter].value) != EOF)
            {
                counter++;
            }

            fclose(valuesFile);

            // Read values from the colliders file and assign them to the tilemap
            FILE *collidersFile = fopen(collidersMap, "rt");
            counter = 0;
            temp = 0;

            while (fscanf(collidersFile, "%i", &temp) != EOF)
            {
                map.tiles[counter].collider = temp;
                counter++;
            }

            fclose(collidersFile);
        }
        else if (strcmp(fileExt, ".bmp") == 0)
        {
            Image image = LoadImage(valuesMap);

            map.tileCountX = image.width;
            map.tileCountY = image.height;

            // TODO: Load tile data from image pixel data

            // NOTE: When using images to codify map data,
            // lot of extra information can be codified in each pixel!
        }
    }

    return map;
}

void DrawTilemap(Tilemap map, Texture2D tileset, Color color, int *tileIndices)
{
    for (int y = 0; y < map.tileCountY; y++)
    {
        for (int x = 0; x < map.tileCountX; x++)
        {

            // each 4 bytes contains rectangle value
            int tileIndex = map.tiles[y * map.tileCountX + x].value - 1;
            // tileIndex equivalent a line of tileset_rects file
            int offset = tileIndex * 4;
            Rectangle rec = {(float)tileIndices[offset], (float)tileIndices[offset + 1], (float)tileIndices[offset + 2], (float)tileIndices[offset + 3]};
            Vector2 dest = {map.position.x + x * map.tileSize, map.position.y + y * map.tileSize};
            DrawTextureRec(tileset, rec, dest, color);
        }
    }
}

int *LoadIntArrayFromFile(const char *filename, int *size)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        return NULL;
    }

    int capacity = 10;
    int *array = (int *)malloc(capacity * sizeof(int));
    if (array == NULL)
    {
        fclose(file);
        printf("Erro de alocação de memória.\n");
        return NULL;
    }

    int count = 0;
    int value;
    while (fscanf(file, "%d", &value) != EOF)
    {
        if (count >= capacity)
        {
            capacity *= 2;
            int *temp = realloc(array, capacity * sizeof(int));
            if (temp == NULL)
            {
                fclose(file);
                free(array);
                printf("Erro de realocação de memória.\n");
                return NULL;
            }
            array = temp;
        }
        array[count++] = value;
    }

    fclose(file);
    *size = count;
    return array;
}

void UnloadTilemap(Tilemap map)
{
    if (map.tiles != NULL)
        free(map.tiles);
}
