#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "game.h"
#include "graphics/graphics.h"

class State
{
public:
    virtual void init(Graphics* graphics) = 0;
    virtual void clean() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvents(Game* game) = 0;
    virtual void update(Game* game, int ms) = 0;
    virtual void draw() = 0;

    void ChangeState(Game* game, State* state) { game->changeState(state); }

protected:
    State() {}
    Graphics* m_Graphics;
};

#endif // GAMESTATE_H
