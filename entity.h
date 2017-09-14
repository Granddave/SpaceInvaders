#ifndef ENTITY_H
#define ENTITY_H

#include "gameobject.h"
#include "globals.h"

class Entity : public GameObject
{
public:
    Entity(Graphics& graphics, const std::string& filePath,
           int srcX, int srcY, int width, int height,
           float posX, float posY, Vec2f speed);

    ~Entity();

protected:
    Vec2f m_Speed;
    bool m_IsMoving;
    bool m_Alive;
};

#endif // ENTITY_H
