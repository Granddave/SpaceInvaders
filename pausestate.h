#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include <SDL.h>
#include "gamestate.h"
#include "input.h"
#include "button.h"

class PauseState : public GameState
{
public:
    void init(Graphics *graphics);
    void clean();

    void pause();
    void resume();

    void handleEvents(Game* game);
    void update(Game* game, int ms);
    void draw(Graphics& graphics);

    static PauseState* instance()
    {
        return &m_PauseState;
    }

protected:
    PauseState() {}

private:
    static PauseState m_PauseState;
    Input m_Input;


};

#endif // PAUSESTATE_H