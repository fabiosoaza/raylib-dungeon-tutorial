#include "../include/game.h"

typedef enum _GameState
{
    PAUSED,
    PLAYING,
    GAME_OVER,
    WON,
    DEAD
} GameState;



Game NewGame()
{
    return (Game){
        .state = DEAD};
}
