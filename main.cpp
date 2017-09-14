#include <iostream>
#include <algorithm>

#include "game.h"
#include "menustate.h"
#include "globals.h"
#include "timer.h"

#undef main
int main(int argc, char* argv[])
{
    (void) argc, argv;

    Game game;
    if(!game.init())
    {
        game.clean();
        return 1;
    }

    game.changeState(MenuState::instance());

    Timer secondTimer;
    Timer updateTimer;
    secondTimer.start();
    updateTimer.start();
    while(game.running())
    {
        game.handleEvents();

        if(secondTimer.getTicks() > 1000)
        {
            std::cout << "Current FPS: " << 1000 / (updateTimer.getTicks() + 1)  << "\n";
            secondTimer.restart();
        }

        game.update(std::min((int)updateTimer.getTicks(), (int)globals::MAX_FRAME_TIME));
        updateTimer.restart();

        game.draw();
    }

    game.clean();
    return 0;
}
