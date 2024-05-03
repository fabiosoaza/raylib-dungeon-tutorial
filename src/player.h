#pragma once
#include "base.h"

GameObject NewPlayer();
void DrawPlayer(GameObject *player);
void LoadPlayerTextures(GameObject *player);
void UnloadPlayerTextures(GameObject *player);
void UpdatePlayer(GameObject *player, float elapsedTime);
