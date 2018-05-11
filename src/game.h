#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>

#include "graphics/graphics.h"
#include "graphics/button.h"
#include "entities/player.h"
#include "utils/timer.h"
#include "utils/fpscounter.h"

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
    void update();
    void draw();

    void clean();

    bool running()  { return m_Running; }
    void quit()     { m_Running = false; }

private:
    std::vector<GameState*> m_States;
    Graphics m_Graphics;
    Timer tickTimer;
    Timer updateTimer;
    Timer capTimer;
    FpsCounter m_Fps;
    bool m_Running;
};

#endif // GAME_H
