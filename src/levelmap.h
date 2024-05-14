#pragma once

#include "raylib.h"
#include "../include/sprite.h"

typedef enum _CollisionType
{

    NON_SOLID,
    SOLID,
    SEMI_SOLID

} CollisionType;

typedef struct _TileId
{

    int id;
    Vector2 atlasOffset;
    Vector2 size;
    CollisionType collider;

} TileId;

typedef struct Tile
{
    TileId id;
    CollisionType collider; // Tile collider (0 -> walkable)
} Tile;

typedef struct _LevelMap
{
    TileId *tiles;
    int cols;
    int rows;
    Texture2D tileset;
    Vector2 position;
}  LevelMap;

LevelMap LoadLevelMapFromFile(char *path);
void LoadLevelMapTextures(LevelMap *map, char *path);
void DrawLevelMapScaled(LevelMap *map, int scale);
void UnloadLevelMap(LevelMap *map);
void UnloadLevelMapTextures(LevelMap *map);