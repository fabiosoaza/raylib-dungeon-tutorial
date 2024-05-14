#include "raylib.h"
#include "player.h"
#include "json_serialize.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "levelmap.h"
#include "../include/sprite.h"
#include "../include/actor.h"
#include "../include/game.h"

#include "settings.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

bool PlayerCollidedMap();

#define TILESET_TILES 32

#define ROWS WORLD_HEIGHT / TILE_SIZE
#define COLS WORLD_WIDTH / TILE_SIZE

static Actor player = {0};

typedef enum PlayerState
{
  PLAYER_IDLE,
  PLAYER_RUN,
  PLAYER_JUMP,

  PLAYER_STATE_COUNT
};

typedef struct Solid
{
  Rectangle base;
  short state;
  Tile tile;

} Solid;

typedef struct _WorldCell
{
  Actor *actor;
  Solid *solid;

} WorldCell;

typedef struct _World
{
  WorldCell cells[WORLD_HEIGHT * WORLD_WIDTH];

} World;

static LevelMap level = {0};

Texture2D playerTexture = {0};



static void ResetPlayer();

void InitTestScene(Game *game)
{

  level = LoadLevelMapFromFile(PATH_LEVEL_MAP);

  LoadLevelMapTextures(&level, PATH_LEVEL_MAP_TEXTURE);

  playerTexture = LoadTexture(PATH_SPRITE_TEXTURE);
  player = NewPlayer(&playerTexture, (Vector2){.x = SCREEN_WIDTH / 2, .y = SCREEN_HEIGHT / 3}, SCALE, true, PLAYER_IDLE);
  player.sprite.color = BACKGROUND_COLOR;
  player.sprite.tileset = &playerTexture;
  player.acceleration.y = GRAVITY;
}

void UpdateTestScene(Game *game, float elapsedTime)
{

  UpdatePlayer(&player, elapsedTime);
 // PlayerCollidedMap();
  // camera.target = (Vector2){sprite.rect.base.x + 20.0f, sprite.rect.base.y + 20.0f};
}

void DrawTestScene(Game *game)
{
  ClearBackground(BACKGROUND_COLOR);

  // BeginMode2D(camera);

  DrawLevelMapScaled(&level, SCALE);
  DrawSprite(&player.sprite);

  // EndMode2D();
}

void UnloadTestScene(Game *game)
{

  UnloadTexture(*(player.sprite.tileset));
  UnloadLevelMap(&level);
}

void PollEventsTestScene(Game *game)
{

  if (IsKeyDown(KEY_UP))
  {

    
  }
  else if (IsKeyDown(KEY_DOWN))
  {
    
  }
  else if (IsKeyUp(KEY_UP) && IsKeyUp(KEY_DOWN))
  {
    
  }

  if (IsKeyDown(KEY_LEFT))
  {

    player.direction.x = -1;
  }
  else if (IsKeyDown(KEY_RIGHT))
  {
    player.direction.x = 1;
  }
  else if (IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_RIGHT))
  {
    player.direction.x = 0;
  }

  if (IsKeyPressed(KEY_SPACE))
  {
    player.speed.y = JUMP_SPEED;
    player.direction.y = -1;
    // player.speed.x += player.solidSpeed.x;
    // player.speed.y += player.solidSpeed.y;
    // play_sound("jump");
    player.grounded = false;
    player.state = PLAYER_JUMP;
  }
}

bool PlayerCollidedMap()
{
  bool collided = false;
  if (GetActorRight(player) >= SCREEN_WIDTH)
  {
    player.base.x = SCREEN_WIDTH - player.base.width - 1;
    player.direction.x = 0;
    collided = true;
  }

  else if (player.base.x <= 0)
  {
    player.base.x = 1;
    player.direction.x = 0;
    collided = true;
  }

  if (GetActorBottom(player) >= SCREEN_HEIGHT)
  {
    player.base.y = SCREEN_HEIGHT - player.base.height - 1;
    player.direction.y = 0;
    collided = true;
  }

  else if (player.base.y <= 0)
  {
    player.base.y = 1;
    player.direction.y = 0;
    collided = true;
  }

  return collided;
}

static void ResetPlayer()
{
  player.speed = (Vector2){PLAYER_SPEED_X, PLAYER_SPEED_Y};
  player.direction = (Vector2){0, 0};
}
