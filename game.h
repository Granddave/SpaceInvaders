#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>

#include "graphics.h"
#include "button.h"
#include "player.h"


class Game
{


public:
    Game();

    bool run();
    void draw(Graphics &graphics);
    void update(float ms);
    void close();

private:
    Player* m_Player;
    Button* m_Button;
};

#endif // GAME_H
