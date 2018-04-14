#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>

#include "graphics.h"
#include "button.h"
#include "player.h"

class GameState;

class Game
{
public:
    Game();

    bool init();
    void exec();
    void changeState(GameState* state);
    void pushState(GameState* state);
    void popState();

    void handleEvents();
    void update(int ms);
    void draw();

    void clean();

    bool running()  { return m_Running; }
    void quit()     { m_Running = false; }

private:
    std::vector<GameState*> m_States;
    Graphics m_Graphics;
    bool m_Running;
};

#endif // GAME_H
