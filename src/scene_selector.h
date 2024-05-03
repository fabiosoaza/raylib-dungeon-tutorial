#pragma once

#include "../include/scene.h"

typedef enum
{
    TEST_SCENE
} SceneType;

void SelectScene(Game *game, GameScene *scene, SceneType type);
