#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <SDL.h>
#include "gamestate.h"
#include "input.h"
#include "player.h"

class PlayState : public GameState
{
public:
    void init(Graphics* graphics);
    void clean();

    void pause();
    void resume();

    void handleEvents(Game* game);
    void update(Game* game, int ms);
    void draw();

    static PlayState* instance()
    {
        return &m_PlayState;
    }

protected:
    PlayState() { m_Graphics = NULL; }

private:
    static PlayState m_PlayState;
    Input m_Input;

    Player* m_Player;
};

#endif // PLAYSTATE_H
