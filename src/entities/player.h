#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "utils/input.h"
#include "bullet.h"
#include "gmath/Vector2.hpp"

#include <vector>
#include <SDL2/SDL_mixer.h>

class Player : public Entity
{
public:
    Player(Graphics* graphics, float posX = 0, float posY = 0);
    virtual ~Player();

    void update(int ms) override;
    void draw(Graphics *graphics) override;

    void handleInput(Input& input);

    Vector2 shootingPos() const { return m_Pos + m_ShootPos; }
    Vector2 shootingVec() const { return m_ShootVec; }
    float damage() const { return m_DamageBase * m_DamageMultiplier; }
    bool isShooting() const { return m_isShooting; }

private:
    void checkBorderCollision();
    void calcMovement(Input& input);
    bool checkIfShoot(Input& input);
    void calcShootingVec();
    void playShootingSound();

    Graphics* m_Graphics;
    float m_ShootCooldown;
    Vector2 m_ShootPos;
    Vector2 m_ShootVec;
    bool m_isShooting;
    float m_DamageBase;
    float m_DamageMultiplier;
    Mix_Chunk* m_ShootSound;
};

#endif // PLAYER_H
