#include "raylib.h"
#include "game.h"
#include "gameobject.h"

GameObject NewGameObject()
{
    return (GameObject){
        .direction = (Vector2){0, 0},
        .base = (Rectangle){0, 0, 0, 0},
        .active = false,
        .speed = (Vector2){0, 0},
        .state = 0

    };
}

Vector2 GetGameObjectPosition(GameObject object)
{
    return (Vector2){object.base.x, object.base.y};
}

Vector2 GetGameObjectCenter(GameObject obj)
{
    return (Vector2){
        .x = obj.base.x + (obj.base.width / 2),
        .y = obj.base.y + (obj.base.height / 2)};
}

bool GameObjectCollided(GameObject obj1, GameObject obj2)
{
    return CheckCollisionRecs(obj1.base, obj2.base);
}

bool GameObjectCollidedFromTop(GameObject obj1, GameObject obj2)
{
    return obj1.direction.y > 0 && GetGameObjectBottom(obj1) > GetGameObjectTop(obj2);
}

bool GameObjectCollidedFromBottom(GameObject obj1, GameObject obj2)
{
    return obj1.direction.y < 0 && GetGameObjectTop(obj1) < GetGameObjectBottom(obj2);
}

bool GameObjectCollidedFromLeft(GameObject obj1, GameObject obj2)
{
    return obj1.direction.x > 0 && GetGameObjectRight(obj1) > GetGameObjectLeft(obj2);
}

bool GameObjectCollidedFromRight(GameObject obj1, GameObject obj2)
{
    return obj1.direction.x > 0 && GetGameObjectRight(obj1) > GetGameObjectLeft(obj2);
}

float GetGameObjectRight(GameObject obj) { return obj.base.x + obj.base.width; }
float GetGameObjectBottom(GameObject obj) { return obj.base.y + obj.base.height; }
float GetGameObjectLeft(GameObject obj) { return obj.base.x; }
float GetGameObjectTop(GameObject obj) { return obj.base.y; }
