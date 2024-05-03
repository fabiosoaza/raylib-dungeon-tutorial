#include "raylib.h"
#include "base.h"

void DrawGameObjectTexture(GameObject *object, float rotation)
{
    Rectangle sourceRect =
        (Rectangle){0, 0, object->texture.width, object->texture.height};
    Rectangle destRect =
        (Rectangle){object->base.x, object->base.y, object->base.width, object->base.height};

    DrawTexturePro(object->texture, sourceRect, destRect, (Vector2){0, 0}, rotation,
                   object->color);
}

void LoadGameObjectTexture(GameObject * object, char *path)
{
    object->texture = LoadTexture(path);
}

void UnLoadGameObjectTexture(GameObject *object)
{
    UnloadTexture(object->texture);
}

Vector2 GetGameObjectPosition(GameObject object)
{
    return (Vector2){object.base.x, object.base.y};
}

Vector2 GetGameObjectCenter(GameObject obj)
{
    return (Vector2)
    {
        .x = obj.base.x + (obj.base.width / 2),
        .y = obj.base.y + (obj.base.height / 2)
    };
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
