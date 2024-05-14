#include "raylib.h"
#include "levelmap.h"
#include "../include/sprite.h"
#include "../include/utils.h"
#include <stddef.h>

#define COLLISION_NON_SOLID 0
#define COLLISION_SOLID 1
#define COLLISION_SEMI_SOLID 2

static TileId EMPTY_TILE = {
    .id = -1,
    .atlasOffset = (Vector2){.x = 0, .y = 0},
    .size = (Vector2){.x = 8, .y = 8},
    .collider = COLLISION_NON_SOLID};

static TileId BACKGROUND_BLACK = {.id = 0, .atlasOffset = (Vector2){.x = 0, .y = 0}, .size = (Vector2){.x = 8, .y = 8}, .collider = COLLISION_NON_SOLID};
static TileId SOLID_PURPLE = {.id = 2, .atlasOffset = (Vector2){.x = 8, .y = 0}, .size = (Vector2){.x = 8, .y = 8}, .collider = COLLISION_SOLID};
static TileId SOLID_BLUE = {.id = 3, .atlasOffset = (Vector2){.x = 16, .y = 0}, .size = (Vector2){.x = 8, .y = 8}, .collider = COLLISION_SOLID};
static TileId SOLID_BROWN = {.id = 4, .atlasOffset = (Vector2){.x = 24, .y = 0}, .size = (Vector2){.x = 8, .y = 8}, .collider = COLLISION_SOLID};

static TileId SOLID_BLUE_GREEN = {.id = 5, .atlasOffset = (Vector2){.x = 0, .y = 16}, .size = (Vector2){.x = 8, .y = 8}, .collider = COLLISION_SOLID};
static TileId BACKGROUND_BLUE = {.id = 6, .atlasOffset = (Vector2){.x = 8, .y = 16}, .size = (Vector2){.x = 8, .y = 8}, .collider = COLLISION_NON_SOLID};
static TileId SOLID_LEFT_PIKE = {.id = 7, .atlasOffset = (Vector2){.x = 16, .y = 16}, .size = (Vector2){.x = 8, .y = 8}, .collider = COLLISION_SOLID};
static TileId SOLID_TOP_PIKE = {.id = 8, .atlasOffset = (Vector2){.x = 24, .y = 16}, .size = (Vector2){.x = 8, .y = 8}, .collider = COLLISION_SOLID};

static inline TileId GetTileById(int tileId)
{
    switch (tileId)
    {
    case 0:
        return BACKGROUND_BLACK;
        break;
    case 2:
        return SOLID_PURPLE;
        break;
    case 3:
        return SOLID_BLUE;
        break;
    case 4:
        return SOLID_BROWN;
        break;
    case 5:
        return SOLID_BLUE_GREEN;
        break;
    case 6:
        return BACKGROUND_BLUE;
        break;
    case 7:
        return SOLID_LEFT_PIKE;
        break;
    case 8:
        return SOLID_TOP_PIKE;
        break;
    default:
        return EMPTY_TILE;
    }
}

LevelMap LoadLevelMapFromFile(char *path)
{
    LevelMap map = {0};
    map.cols = 0;
    map.rows = 0;
    map.position = (Vector2){0, 0};

    IntMatrix intMatrix = LoadIntMatrixFromFile(path, ",");

    if (intMatrix.data == NULL)
    {
        return map;
    }

    map.cols = intMatrix.cols;
    map.rows = intMatrix.rows;
    int dataSize = intMatrix.cols * intMatrix.rows;

    map.tiles = (TileId *)malloc(dataSize * sizeof(TileId));

    for (int i = 0; i < dataSize; i++)
    {
        TileId tile = GetTileById(intMatrix.data[i]);
        map.tiles[i] = tile;
    }

    free(intMatrix.data);

    return map;
}

void LoadLevelMapTextures(LevelMap *map, char *path)
{
    map->tileset = LoadTexture(path);
}

void UnloadLevelMapTextures(LevelMap *map)
{
    UnloadTexture(map->tileset);
}

void DrawLevelMapScaled(LevelMap *map, int scale)
{
    for (int y = 0; y < map->rows; y++)
    {
        for (int x = 0; x < map->cols; x++)
        {
            TileId tile = map->tiles[y * map->cols + x];
            if (tile.id == EMPTY_TILE.id)
            {
                continue;
            }
            float tileSizeX = tile.size.x * scale;
            float tileSizeY = tile.size.y * scale;
            Rectangle source = {tile.atlasOffset.x, tile.atlasOffset.y, tile.size.x, tile.size.y};
            Rectangle destin = {map->position.x + x * tileSizeX, map->position.y + y * tileSizeY, tileSizeX, tileSizeY};
            // Vector2 position = {map->position.x + x * tileSizeX, map->position.y + y * tileSizeY};
            DrawTexturePro(map->tileset, source, destin, map->position, 1.0f, WHITE);
        }
    }
}

void UnloadLevelMap(LevelMap *map)
{
    if (map != NULL && map->tiles != NULL)
    {
        MemFree(map->tiles);
    }
}