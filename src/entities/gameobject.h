#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "utils/globals.h"
#include "graphics/graphics.h"
#include "graphics/sprite.h"
#include "gmath/Vector2.hpp"

#include <SDL2/SDL.h>
#include <memory>

class GameObject
{
public:
    GameObject(Graphics *graphics, const std::string& filePath,
                       int srcX, int srcY, int width, int height,
                       float posX, float posY);
    ~GameObject();

    Vector2 getSize();
    void setPos(float x, float y);
    Vector2 getPos();

    bool deleteLater() { return m_DeleteLater; }

    virtual void update(int ms) = 0;
    virtual void draw(Graphics* graphics);

protected:
    Vector2 m_Pos;
    Sprite m_Sprite;
    bool m_DeleteLater;
};

#endif // GAMEOBJECT_H
