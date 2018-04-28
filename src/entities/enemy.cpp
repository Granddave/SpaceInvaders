#include "enemy.h"
#include <random>

Enemy::Enemy(Graphics *graphics, float posX, float posY)
    : GameObject(graphics,"res/spaceinvaders.png",21,3,12,8, posX, posY)
{
    m_Scale = 1.5f;

    std::random_device rd;
    std::mt19937 gen(rd());
    float mag = 0.5f;
    std::uniform_real_distribution<> dis(0, 1.0f * mag);
    m_Velocity = Vector2((float)(dis(gen) - mag/2), (float)(dis(gen) - mag/2));
}

void Enemy::update(int ms)
{
    m_Pos += m_Velocity * ms * Graphics::s_Scale;

    if (m_Pos.X + getSize().X >= Graphics::s_ScreenWidth || m_Pos.X <= 0)
        m_Velocity = Vector2::Reflect(m_Velocity, Vector2(1, 0));
    if (m_Pos.Y + getSize().Y >= Graphics::s_ScreenHeight || m_Pos.Y <= 0)
        m_Velocity = Vector2::Reflect(m_Velocity, Vector2(0, 1));

    if(m_Alive == false)
        m_DeleteLater = true;
}

void Enemy::draw(Graphics *graphics)
{
    if(m_Alive)
        m_Sprite.draw(graphics, m_Pos.X, m_Pos.Y, m_Scale);
}
