#pragma once

#include "raylib.h"

typedef struct _Sprite
{

    Texture2D * tileset; // spritesheet
    Color color;
    Vector2 atlasOffset;
    Rectangle rect;
    int numAnimations; // total animations in spritesheet
    int animationTimeInFrames; // time to run each animation
    int currentAnimation;//sprite sheet line
    int currentAnimationIndex;//animation index
    bool animate;
    bool flipX;
    bool flipY;
    bool visible;
    float rotation;
    float scale;
} Sprite;

void DrawSprite(Sprite *object);
