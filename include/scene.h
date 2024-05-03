#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "game.h"

#define CALL_IF_NOT_NULL(function) \
{\
    if (function!=NULL){\
        function();\
    }\
}\


typedef void (*SceneAction)(Game *);
typedef void (*SceneActionUpdate)(Game *, float);

typedef struct GameScene
{
    SceneAction initScene;
    SceneActionUpdate updateScene;
    SceneAction drawScene;
    SceneAction unloadScene;
    int state;
    bool loaded;
} GameScene;
