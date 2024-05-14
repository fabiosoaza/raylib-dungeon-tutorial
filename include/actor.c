#include <raylib.h>
#include "actor.h"

bool ActorCollided(Actor actor, Rectangle obj2)
{
    return CheckCollisionRecs(actor.base, obj2);
}

bool ActorCollidedFromTop(Actor actor, Rectangle obj2)
{
    return actor.direction.y > 0 && GetActorBottom(actor) > obj2.y;
}

bool ActorCollidedFromBottom(Actor actor, Rectangle obj2)
{
    return actor.direction.y < 0 && GetActorTop(actor) < obj2.y + obj2.height;
}

bool ActorCollidedFromLeft(Actor actor, Rectangle obj2)
{
    return actor.direction.x > 0 && GetActorRight(actor) > obj2.x;
}

bool ActorCollidedFromRight(Actor actor, Rectangle obj2)
{
    return actor.direction.x < 0 && GetActorLeft(actor) > obj2.x + obj2.width;
}

float GetActorRight(Actor obj) { return obj.base.x + obj.base.width; }
float GetActorBottom(Actor obj) { return obj.base.y + obj.base.height; }
float GetActorLeft(Actor obj) { return obj.base.x; }
float GetActorTop(Actor obj) { return obj.base.y; }
