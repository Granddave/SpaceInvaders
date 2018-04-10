#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "input.h"
#include "bullet.h"
#include <vector>
#include <SDL2/SDL_mixer.h>

class Player : public Entity
{
public:
    Player(Graphics* graphics, float posX = 0, float posY = 0);
    ~Player();

    void update(int ms) override;
    void draw(Graphics *graphics) override;

    void handleInput(Input& input);

private:
    Graphics* m_Graphics;
    float m_ShootCooldown;
    Vec2 m_ShootPos;
    Mix_Chunk* m_ShootSound;
    std::vector<Bullet> m_Bullets;
};

#endif // PLAYER_H
