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

    Vec2f shootingPos() const { return m_Pos + m_ShootPos; }
    Vec2f shootingVec() const { return m_ShootVec; }
    float damage() const { return m_DamageBase * m_DamageMultiplier; }
    bool isShooting() const { return m_isShooting; }

private:
    Graphics* m_Graphics;
    float m_ShootCooldown;
    Vec2f m_ShootPos;
    Vec2f m_ShootVec;
    bool m_isShooting;
    float m_DamageBase;
    float m_DamageMultiplier;
    Mix_Chunk* m_ShootSound;
};

#endif // PLAYER_H
