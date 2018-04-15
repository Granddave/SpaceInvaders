#ifndef ENTITY_H
#define ENTITY_H

#include "gameobject.h"
#include "globals.h"
#include "gmath/Vector2.hpp"

class Entity : public GameObject
{
public:
    Entity(Graphics* graphics, const std::string& filePath,
           int srcX, int srcY, int width, int height,
           float posX, float posY, Vector2 speed);
protected:
    Vector2 m_Velocity;
    Vector2 m_Acceleration;
    bool m_Alive;
};

#endif // ENTITY_H
