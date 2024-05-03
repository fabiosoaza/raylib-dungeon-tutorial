#include "raylib.h"
#include "base.h"
#include "player.h"
#include "tilemap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void PollEvents();

bool PlayerCollidedMap();

static Rectangle oldPlayer;

static Texture2D texTileset;
static Tilemap tilemap;

static int *tilesetRects;
static GameObject gamePlayer = {0};

#define TILESET_TILES 32

#define PLAYER_COLLISION_PADDING 12 // Player padding to detect collision with walls

void InitTestScene(Game *game)
{

  texTileset = LoadTexture("resources/gfx/tileset.png");

  int tilesetRectsSize = 0;
  tilesetRects = LoadIntArrayFromFile("resources/tilemaps/tileset_rectangles.txt", &tilesetRectsSize);

  // LESSON 06: Load tilemap data: tile values (tileset index) and tile colliders
  tilemap = LoadTilemap("resources/tilemaps/tilemap.txt", "resources/tilemaps/tilemap_colliders.txt");

  tilemap.tileSize = 32;
  tilemap.position = (Vector2){SCREEN_WIDTH / 2 - tilemap.tileCountX * tilemap.tileSize / 2,
                               SCREEN_HEIGHT / 2 - tilemap.tileCountY * tilemap.tileSize / 2};

  gamePlayer = NewPlayer();
  gamePlayer.speed = (Vector2){PLAYER_SPEED_X, PLAYER_SPEED_Y};
  gamePlayer.base = (Rectangle){tilemap.position.x + 1 * tilemap.tileSize + 8, tilemap.position.y + 1 * tilemap.tileSize + 8, 8, 8};
  gamePlayer.direction = (Vector2){0, 1};
  gamePlayer.color = BACKGROUND_COLOR;
  LoadPlayerTextures(&gamePlayer);
  
  
  oldPlayer = gamePlayer.base;
}

void UpdateTestScene(Game *game, float elapsedTime)
{
  oldPlayer = gamePlayer.base;

  // Atualiza a posição do jogador se não houver colisão
  PollEvents();

  UpdatePlayer(&gamePlayer, elapsedTime);

  if (PlayerCollidedMap())
  {
    gamePlayer.base = oldPlayer;
  }
}

void DrawTestScene(Game *game)
{
  ClearBackground(WHITE);

  DrawTilemap(tilemap, texTileset, WHITE, tilesetRects);

  DrawPlayer(&gamePlayer);
}

void UnloadTestScene(Game *game)
{
  UnloadPlayerTextures(&gamePlayer);
  UnloadTilemap(tilemap);
  UnloadTexture(texTileset);
  if (tilesetRects != NULL)
  {
    free(tilesetRects);
  }
}

static void PollEvents()
{

  if (IsKeyDown(KEY_UP))
  {

    gamePlayer.direction.y = -1;
  }
  else if (IsKeyDown(KEY_DOWN))
  {
    gamePlayer.direction.y = 1;
  }
  else if (IsKeyUp(KEY_UP) && IsKeyUp(KEY_DOWN))
  {
    gamePlayer.direction.y = 0;
  }

  if (IsKeyDown(KEY_LEFT))
  {

    gamePlayer.direction.x = -1;
  }
  else if (IsKeyDown(KEY_RIGHT))
  {
    gamePlayer.direction.x = 1;
  }
  else if (IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_RIGHT))
  {
    gamePlayer.direction.x = 0;
  }

  if (IsKeyPressed(KEY_SPACE))
  {
  }
}

bool PlayerCollidedMap()
{

  bool collided = false;
  for (int y = 0; y < tilemap.tileCountY; y++)
  {
    for (int x = 0; x < tilemap.tileCountX; x++)
    {
      // TODO: Review player padding for a better collision with walls
      bool is_tile_collider = tilemap.tiles[y * tilemap.tileCountX + x].collider == 0;
      Rectangle playerRect = (Rectangle){gamePlayer.base.x + PLAYER_COLLISION_PADDING, gamePlayer.base.y + PLAYER_COLLISION_PADDING, gamePlayer.base.width, gamePlayer.base.height};
      Rectangle tileRect = (Rectangle){tilemap.position.x + x * tilemap.tileSize + PLAYER_COLLISION_PADDING, tilemap.position.y + y * tilemap.tileSize + PLAYER_COLLISION_PADDING, tilemap.tileSize, tilemap.tileSize};
      if (is_tile_collider && CheckCollisionRecs(playerRect, tileRect))
      {
        return true;
      }
    }
  }
  return false;
}
