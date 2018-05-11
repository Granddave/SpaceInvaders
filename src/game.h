#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>

#include "graphics/graphics.h"
#include "graphics/button.h"
#include "entities/player.h"

class State;

class Game
{
public:
    Game();

    bool init();
    void exec();
    void changeState(State* state);
    void pushState(State* state);
    void popState();

    void handleEvents();
    void update(int ms);
    void draw();

    void clean();

    bool running()  { return m_Running; }
    void quit()     { m_Running = false; }

private:
    std::vector<State*> m_States;
    Graphics m_Graphics;
    bool m_Running;
};

#endif // GAME_H
