#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

#include "states/gamestate.h"
#include "utils/input.h"
#include "entities/player.h"
#include "entities/bullet.h"
#include "entities/enemy.h"

class PlayState : public GameState
{
public:
    void init(Graphics* graphics);
    void clean();

    void pause();
    void resume();

    void handleEvents(Game* game);
    void update(Game* game, int ms);
    void draw();

    static PlayState* instance()
    {
        return &m_PlayState;
    }

protected:
    PlayState() { m_Graphics = NULL; }

private:
    static PlayState m_PlayState;
    Input m_Input;

    b2World* m_World;

// Temp
    b2Body* m_GroundBody;
    b2Body* m_Body;
// Temp

    Player* m_Player;
    std::vector<Enemy> m_Enemies;
    std::vector<Bullet> m_PlayerBullets;
};

#endif // PLAYSTATE_H
