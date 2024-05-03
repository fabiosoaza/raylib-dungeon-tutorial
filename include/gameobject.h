#pragma once
#include "raylib.h"
#include <stdbool.h>

typedef struct _GameObject
{
    Rectangle base;
    Vector2 speed;
    Vector2 direction;
    bool active;
    short state;
    Texture2D texture;
    Color color;
} GameObject;



void LoadGameObjectTexture(GameObject *object, char * path);
void UnLoadGameObjectTexture(GameObject *object);
void DrawGameObjectTexture(GameObject *object, float rotation);

Vector2 GetGameObjectPosition(GameObject object);
bool GameObjectCollided(GameObject obj1, GameObject obj2);
bool GameObjectCollidedFromTop(GameObject obj1, GameObject obj2);
bool GameObjectCollidedFromBottom(GameObject obj1, GameObject obj2);
bool GameObjectCollidedFromLeft(GameObject obj1, GameObject obj2);
bool GameObjectCollidedFromRight(GameObject obj1, GameObject obj2);
Vector2 GetGameObjectCenter(GameObject obj1);

float GetGameObjectRight(GameObject GameObject);
float GetGameObjectBottom(GameObject GameObject);
float GetGameObjectTop(GameObject GameObject);
float GetGameObjectLeft(GameObject GameObject);

