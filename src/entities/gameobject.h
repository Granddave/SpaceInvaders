#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "utils/globals.h"
#include "graphics/graphics.h"
#include "graphics/sprite.h"
#include "gmath/Vector2.hpp"

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include <memory>

class GameObject
{
public:
    GameObject(Graphics *graphics, const std::string& filePath,
                       int srcX, int srcY, int width, int height,
                       float posX, float posY);
    GameObject();
    ~GameObject();

    Vector2 getSize();
    void setPos(float x, float y);
    Vector2 getPos();

    bool deleteLater() { return m_DeleteLater; }

    virtual void update(int ms) = 0;
    virtual void draw(Graphics* graphics);

protected:
    b2Body* m_Body;
    Vector2 m_Pos;          // Todo: Refactor away
    Vector2 m_Velocity;     //
    Vector2 m_Acceleration; //
    Sprite m_Sprite;
    float m_Scale;          // Todo: Refactor
    bool m_Alive;
    bool m_DeleteLater;
};

#endif // GAMEOBJECT_H
