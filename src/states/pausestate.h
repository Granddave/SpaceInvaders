#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "states/state.h"
#include "utils/input.h"
#include "graphics/button.h"

#include <SDL2/SDL.h>

class PauseState : public State
{
public:
    void init(Graphics *graphics);
    void clean();

    void pause();
    void resume();

    void handleEvents(Game* game);
    void update(Game* game, int ms);
    void draw();

    static PauseState* instance()
    {
        return &m_PauseState;
    }

protected:
    PauseState() { m_Graphics = NULL; }

private:
    static PauseState m_PauseState;
    Input m_Input;


};

#endif // PAUSESTATE_H
