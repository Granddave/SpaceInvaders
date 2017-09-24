#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"

class Bullet : public GameObject
{
public:
    Bullet(Graphics *graphics, float posX, float posY, int damage, Vec2f speed);

    void update(int ms);
    void draw(Graphics *graphics);
private:
    int m_Damage;
    bool m_HasHit;
    Vec2f m_Velocity;
};

#endif // BULLET_H
