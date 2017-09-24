#ifndef ENTITY_H
#define ENTITY_H

#include "gameobject.h"
#include "globals.h"

class Entity : public GameObject
{
public:
    Entity(Graphics* graphics, const std::string& filePath,
           int srcX, int srcY, int width, int height,
           float posX, float posY, Vec2f speed);
protected:
    Vec2f m_Velocity;
    Vec2f m_Acceleration;
    bool m_Alive;
};

#endif // ENTITY_H
