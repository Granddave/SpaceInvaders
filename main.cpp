#include "game.h"
#include "menustate.h"
#include "globals.h"
#include "timer.h"

#include <iostream>
#include <algorithm>

int main(int argc, char* argv[])
{
    (void) argc;
    std::cout << argv[0] << std::endl;

    Game game;
    if(!game.init())
    {
        game.clean();
        return -1;
    }

    game.changeState(MenuState::instance());

#if PRINT_FPS
    Timer secondTimer;
    secondTimer.start();
#endif
    Timer updateTimer;
    updateTimer.start();
    while(game.running())
    {
        game.handleEvents();
#if PRINT_FPS
        if(secondTimer.getTicks() > 1000)
        {
            std::cout << "Current FPS: " << 1000 / (updateTimer.getTicks() + 1)  << "\n";
            secondTimer.restart();
        }
#endif
        game.update(std::min((int)updateTimer.getTicks(), Graphics::s_MaxFrameTime));
        updateTimer.restart();

        game.draw();
    }

    game.clean();
    return 0;
}
