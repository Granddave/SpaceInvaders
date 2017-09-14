#include "gamestate.h"

void GameState::ChangeState(Game *game, GameState *state)
{
    game->changeState(state);
}
