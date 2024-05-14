#pragma once
#include <raylib.h>
#include "sprite.h"

typedef struct _Actor
{
    Sprite sprite;
    Rectangle base;
    Vector2 speed;
    Vector2 acceleration;
    Vector2 direction;
    short state;
    bool grounded;

} Actor;

bool ActorCollided(Actor actor, Rectangle obj2);

bool ActorCollidedFromTop(Actor actor, Rectangle obj2);

bool ActorCollidedFromBottom(Actor actor, Rectangle obj2);

bool ActorCollidedFromLeft(Actor actor, Rectangle obj2);

bool ActorCollidedFromRight(Actor actor, Rectangle obj2);

float GetActorRight(Actor obj);
float GetActorBottom(Actor obj);
float GetActorLeft(Actor obj);
float GetActorTop(Actor obj);
