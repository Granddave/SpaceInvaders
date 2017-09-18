#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <memory>
#include "globals.h"
#include "graphics.h"
#include "sprite.h"


class GameObject
{
public:
    GameObject(Graphics *graphics, const std::string& filePath,
                       int srcX, int srcY, int width, int height,
                       float posX, float posY);
    ~GameObject();

    virtual void update(int ms) = 0;
    virtual void draw(Graphics* graphics);

protected:
    Vec2f m_Pos;
    Sprite* m_Sprite;
};

#endif // GAMEOBJECT_H
