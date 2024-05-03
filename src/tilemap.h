#pragma once

#include "raylib.h"


// LESSON 06: Tile struct
typedef struct Tile
{
  int value;     // Tile index value (in tileset)
  bool collider; // Tile collider (0 -> walkable)
  Color color;   // Tile color (could be useful)
} Tile;

// LESSON 06: Tilemap struct
typedef struct Tilemap
{
  Tile *tiles;      // Tiles data
  int tileCountX;   // Tiles counter X
  int tileCountY;   // Tiles counter Y
  int tileSize;     // Tile size (XY)
  Vector2 position; // Tilemap position in screen
} Tilemap;

int *LoadIntArrayFromFile(const char *filename, int *size);
Tilemap LoadTilemap(const char *valuesMap, const char *collidersMap); // Load tilemap data from file
void UnloadTilemap(Tilemap map);                                      // Unload tilemap data
void DrawTilemap(Tilemap map, Texture2D tileset, Color color, int *tileIndices);
