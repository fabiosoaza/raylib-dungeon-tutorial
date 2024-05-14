#include "raylib.h"
#include "player.h"
#include <stdbool.h>
#include <stdio.h>

/*
typedef enum
{
    SPRITE_DICE,
    SPRITE_PLAYER,
    SPRITE_PLAYER_RUN,
    SPRITE_PLAYER_JUMP,
    SPRITE_BUTTON_PLAY,
    SPRITE_BUTTON_SAVE
} SpriteID;

static inline Sprite GetSprite(SpriteID spriteID);

static inline void SetSpriteDimensions(Sprite *sprite, int atlasOffsetX, int atlasOffsetY, int width, int height);

static inline void SetSpriteDimensions(Sprite *sprite, int atlasOffsetX, int atlasOffsetY, int width, int height)
{
    sprite->atlasOffset.x = atlasOffsetX;
    sprite->atlasOffset.y = atlasOffsetY;
    sprite->size.x = width;
    sprite->size.y = height;
}


static Sprite GetSprite(SpriteID spriteID)
{
    Sprite sprite = {0};
    sprite.flipX = false;
    sprite.flipY = false;
    sprite.rotation = 0;


    switch (spriteID)
    {
    case SPRITE_DICE:
        SetSpriteDimensions(&sprite, 16, 0, 16, 16);
        break;

    case SPRITE_PLAYER:
        SetSpriteDimensions(&sprite, 112, 0, 17, 20);
        break;

    case SPRITE_BUTTON_PLAY:
        SetSpriteDimensions(&sprite, 80, 0, 32, 16);
        break;

    case SPRITE_BUTTON_SAVE:
        SetSpriteDimensions(&sprite, 80, 16, 32, 16);
        break;
    }
    return sprite;
}
*/

Actor NewPlayer(Texture2D *tileset, Vector2 position, float scale, bool active, int state)
{
    Actor actor;

    actor.base = (Rectangle){.x = position.x, .y = position.y, .width = 17, .height = 20};
    actor.direction = (Vector2){0, 0};
    actor.speed = (Vector2){0, 0};
    actor.state = state;
    actor.grounded =true;

    actor.sprite.tileset = tileset;
    actor.sprite.flipX = false;
    actor.sprite.flipY = false;
    actor.sprite.rotation = 0;
    actor.sprite.visible = active;
    actor.sprite.atlasOffset.x = 112;
    actor.sprite.atlasOffset.y = 0;
    actor.sprite.rect = actor.base;
    actor.sprite.scale = scale;

    return actor;
}

void DrawPlayer(Actor *player)
{
    DrawSprite(&player->sprite);
}

/**
 fix32 PHY_calculateJumpSpeed(GameObject *object, fix32 extraGravity) {
    fix32 newVel = object->isGrounded ? FIX32(0) : fix32Add(object->speedY, object->gravity);
    return newVel;
} 
 * 
 * 
*/

void UpdatePlayer(Actor *player, float deltaTime)
{
    // normalize diagonal movement
    // Vector2 direction = player->direction.x != 0 && player->direction.y != 0 ? Vector2Normalize(player->direction) : player->direction;
    // Vector2 direction = Vector2Normalize();
    if(player->grounded == false){
        player->speed.y = - player->speed.y + player->acceleration.y;

    }
    
    Vector2 direction = player->direction;
    player->base.x += (player->speed.x * deltaTime * direction.x);
    player->base.y += (player->speed.y * deltaTime * direction.y);
    player->sprite.rect = player->base;
}
