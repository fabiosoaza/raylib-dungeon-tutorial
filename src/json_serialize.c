#include "json_serialize.h"
#include <stdlib.h>
#include "raylib.h"
#include <cjson/cJSON.h>
#include "../include/gameobject.h"
#include "../include/sprite.h"

char *SerializeGameObject(GameObject gameObject)
{
    cJSON *root = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "baseX", cJSON_CreateNumber(gameObject.base.x));
    cJSON_AddItemToObject(root, "baseY", cJSON_CreateNumber(gameObject.base.y));
    cJSON_AddItemToObject(root, "baseWidth", cJSON_CreateNumber(gameObject.base.width));
    cJSON_AddItemToObject(root, "baseHeight", cJSON_CreateNumber(gameObject.base.height));
    cJSON_AddItemToObject(root, "speedX", cJSON_CreateNumber(gameObject.speed.x));
    cJSON_AddItemToObject(root, "speedY", cJSON_CreateNumber(gameObject.speed.y));
    cJSON_AddItemToObject(root, "directionX", cJSON_CreateNumber(gameObject.direction.x));
    cJSON_AddItemToObject(root, "directionY", cJSON_CreateNumber(gameObject.direction.y));
    cJSON_AddItemToObject(root, "active", cJSON_CreateBool(gameObject.active));
    cJSON_AddItemToObject(root, "state", cJSON_CreateNumber(gameObject.state));

    char *json_string = cJSON_Print(root);
    cJSON_Delete(root);

    return json_string;
}

char *SerializeSprite(Sprite sprite)
{
    cJSON *root = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "atlasOffsetX", cJSON_CreateNumber(sprite.atlasOffset.x));
    cJSON_AddItemToObject(root, "atlasOffsetY", cJSON_CreateNumber(sprite.atlasOffset.y));
    cJSON_AddItemToObject(root, "sizeX", cJSON_CreateNumber(sprite.rect.width));
    cJSON_AddItemToObject(root, "sizeY", cJSON_CreateNumber(sprite.rect.height));

    cJSON_AddItemToObject(root, "textureWidth", cJSON_CreateNumber(sprite.tileset->width));
    cJSON_AddItemToObject(root, "textureHeight", cJSON_CreateNumber(sprite.tileset->height));

    cJSON_AddItemToObject(root, "colorR", cJSON_CreateNumber(sprite.color.r));
    cJSON_AddItemToObject(root, "colorG", cJSON_CreateNumber(sprite.color.g));
    cJSON_AddItemToObject(root, "colorB", cJSON_CreateNumber(sprite.color.b));
    cJSON_AddItemToObject(root, "colorA", cJSON_CreateNumber(sprite.color.a));
    cJSON_AddItemToObject(root, "rotation", cJSON_CreateNumber(sprite.rotation));

    char *json_string = cJSON_Print(root);
    cJSON_Delete(root);

    return json_string;
}
