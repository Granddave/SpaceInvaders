#include "game.h"
#include "utils/utils.h"

#include <iostream>
#include <algorithm>

int main(int argc, char* argv[])
{
    NOT_USED(argc);
    std::cout << argv[0] << std::endl;

    Game game;
    if(!game.init())
    {
        game.clean();
        return -1;
    }
    game.exec();
    return 0;
}
