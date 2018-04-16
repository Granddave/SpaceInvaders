#ifndef BULLET_H
#define BULLET_H

#include "entities/gameobject.h"
#include "gmath/Vector2.hpp"

class Bullet : public GameObject
{
public:
    Bullet(Graphics *graphics, float posX, float posY, int damage, Vector2 speed);

    void update(int ms);
    void draw(Graphics *graphics) override;
private:
    int m_Damage;
    bool m_HasHit;
    Vector2 m_Velocity;
};

#endif // BULLET_H
