#pragma once
#include "raylib.h"

#define WINDOW_TITLE "Celeste Clone"
#define LOG_LEVEL_ENABLE (LOG_DEBUG | LOG_INFO | LOG_WARNING)

#define SCALE 4
#define TILE_SIZE 8 * SCALE

#define SCREEN_WIDTH 320 * SCALE
#define SCREEN_HEIGHT 224 * SCALE
#define TARGET_FPS 60

#define WORLD_WIDTH SCREEN_WIDTH
#define WORLD_HEIGHT SCREEN_HEIGHT

#define BACKGROUND_COLOR WHITE

// delta time returns one hundredth of a second, e.g., 0.016667
#define SPEED_BASE 100

// pixels per second
// delta time returns one hundredth of a second, e.g., 0.016667
#define PLAYER_SPEED_X 4.5 * SPEED_BASE
#define PLAYER_SPEED_Y 4.5 * SPEED_BASE

#define  RUN_SPEED  2.0f * SPEED_BASE
#define  RUN_ACCELERATION  10.0f * SPEED_BASE
#define  RUN_REDUCE  22.0f * SPEED_BASE
#define  FLY_REDUCE  12.0f * SPEED_BASE
#define  GRAVITY  13.0f * SPEED_BASE
#define  FALL_SPEED  3.6f * SPEED_BASE
#define  JUMP_SPEED  3.0f * SPEED_BASE


#define TITLE_FONT_SIZE (2 * TILE_SIZE)
#define TITLE_FONT_SPACING (TILE_SIZE / 2)

#define PATH_LEVEL_MAP "resources/tilemaps/tilemap.csv"
#define PATH_LEVEL_MAP_TEXTURE "resources/tilemaps/tiles.png"
#define PATH_SPRITE_TEXTURE "resources/textures/game_tiles.png"


