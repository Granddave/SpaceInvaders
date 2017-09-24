#include "gameobject.h"

GameObject::GameObject(Graphics* graphics, const std::string& filePath,
                       int srcX, int srcY, int width, int height,
                       float posX, float posY)
    : m_Pos({posX, posY}),
      m_Sprite(graphics, filePath, srcX, srcY, width, height),
      m_DeleteLater(false)
{

}

GameObject::~GameObject()
{

}

Vec2 GameObject::getSize()
{
    return Vec2(m_Sprite.getRect().w, m_Sprite.getRect().h);
}

void GameObject::setPos(float x, float y)
{
    m_Pos.x = x;
    m_Pos.y = y;
}

Vec2f GameObject::getPos()
{
    return m_Pos;
}

void GameObject::draw(Graphics *graphics)
{
    m_Sprite.draw(graphics, m_Pos.x, m_Pos.y);
}
