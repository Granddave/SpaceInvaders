#include "bullet.h"
#include "utils.h"

#include <iostream>
#include <math.h>

const float c_BulletScale  = 2.0f;

Bullet::Bullet(Graphics *graphics, float posX, float posY, int damage, Vector2 velocity)
    : GameObject(graphics, "resources/spaceinvaders.png",
                 31, 21, 1, 4, posX, posY),
      m_Damage(damage),
      m_HasHit(false),
      m_Velocity(velocity)
{

}

void Bullet::update(int ms)
{
    m_Pos += m_Velocity * ms * Graphics::s_Scale;

    int w = Graphics::s_ScreenWidth;
    int h = Graphics::s_ScreenHeight;
    if(!pointInsideRect(m_Pos, SDL_Rect({0, 0, w, h})))
    {
        m_DeleteLater = true;
    }
}

void Bullet::draw(Graphics *graphics)
{
    if(!m_HasHit)
        m_Sprite.draw(graphics, m_Pos.X, m_Pos.Y,
                      atan2(m_Velocity.Y, m_Velocity.X)*180/M_PI + 90,
                      NULL, SDL_FLIP_NONE, Graphics::s_Scale * c_BulletScale);
}

