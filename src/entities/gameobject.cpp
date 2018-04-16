#include "gameobject.h"

GameObject::GameObject(Graphics* graphics, const std::string& filePath,
                       int srcX, int srcY, int width, int height,
                       float posX, float posY)
    : m_Pos({posX, posY}),
      m_Sprite(graphics, filePath, srcX, srcY, width, height),
      m_Scale(1.0f),
      m_DeleteLater(false)
{

}

GameObject::GameObject()
    : m_Scale(1.0f),
      m_DeleteLater(false)
{

}

GameObject::~GameObject()
{

}

Vector2 GameObject::getSize()
{
    return Vector2(m_Sprite.getRect().w, m_Sprite.getRect().h)
            * m_Scale;
}

void GameObject::setPos(float x, float y)
{
    m_Pos.X = x;
    m_Pos.Y = y;
}

Vector2 GameObject::getPos()
{
    return m_Pos;
}

void GameObject::draw(Graphics *graphics)
{
    m_Sprite.draw(graphics, m_Pos.X, m_Pos.Y);
}
