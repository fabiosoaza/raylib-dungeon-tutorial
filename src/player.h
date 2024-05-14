#pragma once
#include <raylib.h>
#include <stdbool.h>
#include "../include/actor.h"

Actor NewPlayer(Texture2D *tileset, Vector2 position, float scale, bool active, int state);
void DrawPlayer(Actor *player);
void UpdatePlayer(Actor *player, float elapsedTime);
