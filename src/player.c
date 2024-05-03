#include "base.h"
#include "player.h"


GameObject NewPlayer()
{
    return (GameObject){
        .direction = (Vector2){0,0},
        .active=true,
    };
}

void LoadPlayerTextures(GameObject *player)
{
    LoadGameObjectTexture(player, "resources/sprites/player.png");
}

void UnloadPlayerTextures(GameObject *player)
{
    UnLoadGameObjectTexture(player);
}

void DrawPlayer(GameObject *player)
{
    DrawGameObjectTexture(player, 0.0f);
}

void UpdatePlayer(GameObject *player, float elapsedTime)
{
    float deltaTime = elapsedTime * 100;
    player->base.x += (player->speed.x * deltaTime * player->direction.x);
    player->base.y += (player->speed.y * deltaTime * player->direction.y);
}
