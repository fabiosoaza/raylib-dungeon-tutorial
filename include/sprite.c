#include "raylib.h"
#include "sprite.h"
#include <stdio.h>

void DrawSprite(Sprite *object)
{

  if (!object->visible)
  {
    return;
  }

  float rotation = object->rotation;

  Rectangle sourceRect =
      (Rectangle){object->atlasOffset.x, object->atlasOffset.y, object->rect.width, object->rect.height};

  Rectangle destRect = {.x = object->rect.x, .y = object->rect.y, .width = object->rect.width * object->scale, .height = object->rect.height * object->scale};

  Texture2D texture = *(object->tileset);



  DrawTexturePro(texture, sourceRect, destRect, (Vector2){0, 0}, rotation, object->color);
}
