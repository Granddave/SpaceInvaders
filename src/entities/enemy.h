#ifndef ENEMY_H
#define ENEMY_H

#include "entities/gameobject.h"

class Enemy : public GameObject
{
public:
    Enemy(Graphics *graphics, float posX, float posY);
    void update(int ms) override;
    void draw(Graphics *graphics) override;
};

#endif // ENEMY_H
