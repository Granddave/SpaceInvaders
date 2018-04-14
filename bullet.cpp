#include "bullet.h"

#include <iostream>
#include <math.h>

const float c_BulletScale  = 2.0f;

Bullet::Bullet(Graphics *graphics, float posX, float posY, int damage, Vec2f velocity)
    : GameObject(graphics, "resources/spaceinvaders.png",
                 31, 21, 1, 4, posX, posY),
      m_Damage(damage),
      m_HasHit(false),
      m_Velocity(velocity)
{

}

void Bullet::update(int ms)
{
    m_Pos.x += m_Velocity.x * ms * Graphics::s_Scale;
    m_Pos.y += m_Velocity.y * ms * Graphics::s_Scale;

    int w = Graphics::s_ScreenWidth;
    int h = Graphics::s_ScreenHeight;
    if(!m_Pos.isInside(SDL_Rect({0, 0, w, h})))
    {
        m_DeleteLater = true;
        m_Pos.y = -20;
    }
}

void Bullet::draw(Graphics *graphics)
{
    if(!m_HasHit)
        m_Sprite.draw(graphics, m_Pos.x, m_Pos.y,
                      atan2(m_Velocity.y, m_Velocity.x)*180/M_PI + 90,
                      NULL, SDL_FLIP_NONE, Graphics::s_Scale * c_BulletScale);
}

