#include <iostream>

#include "game.h"
#undef main
int main(int argc, char* argv[])
{
    (void) argc, argv;
    Game game;

    bool b = game.run();
    game.close();

    return b;
}
