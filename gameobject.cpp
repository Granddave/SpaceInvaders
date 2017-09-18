#include "gameobject.h"

GameObject::GameObject(Graphics* graphics, const std::string& filePath,
                       int srcX, int srcY, int width, int height,
                       float posX, float posY)
    : m_Pos({posX, posY})
{
    m_Sprite = new Sprite(graphics, filePath, srcX, srcY, width, height);
}

GameObject::~GameObject()
{
    delete m_Sprite;
}

void GameObject::draw(Graphics *graphics)
{
    m_Sprite->draw(graphics, m_Pos.x, m_Pos.y);
}
