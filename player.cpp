#include "player.h"
#include <iostream>

const float cPlayerBaseSpeed = 0.5f;

Player::Player(Graphics *graphics, const std::string &filePath,
               int srcX, int srcY, int width, int height,
               float posX, float posY, Vec2f speed)
    : Entity(graphics, filePath, srcX, srcY, width, height, posX, posY, speed)
{

}

Player::~Player()
{

}

void Player::moveLeft()
{
    m_Speed.x = -cPlayerBaseSpeed;
    m_IsMoving = true;
}

void Player::moveRight()
{
    m_Speed.x = cPlayerBaseSpeed;
    m_IsMoving = true;
}

void Player::moveUp()
{
    m_Speed.y = -cPlayerBaseSpeed;
    m_IsMoving = true;
}

void Player::moveDown()
{
    m_Speed.y = cPlayerBaseSpeed;
    m_IsMoving = true;
}

void Player::stopMoving()
{
    m_IsMoving = false;
}

void Player::update(int ms)
{
    if(!m_IsMoving)
    {
        if(m_Speed.x < -0.03f)
            m_Speed.x = m_Speed.x + 0.002f * ms;
        else if(m_Speed.x > 0.03f)
            m_Speed.x = m_Speed.x - 0.002f * ms;
        else m_Speed.x = 0;

        if(m_Speed.y < -0.03f)
            m_Speed.y = m_Speed.y + 0.002f * ms;
        else if(m_Speed.y > 0.03f)
            m_Speed.y = m_Speed.y - 0.002f * ms;
        else m_Speed.y = 0;
    }

    m_Pos.x += m_Speed.x * ms;
    m_Pos.y += m_Speed.y * ms;
}

void Player::draw(Graphics* graphics)
{
    if(m_Alive)
        m_Sprite->draw(graphics, m_Pos.x, m_Pos.y);
}

void Player::handleInput(Input &input)
{
    // Left - Right
    if(input.isKeyHeld(SDL_SCANCODE_A) && input.isKeyHeld(SDL_SCANCODE_D))
        stopMoving();
    else if(input.isKeyHeld(SDL_SCANCODE_A))
        moveLeft();
    else if(input.isKeyHeld(SDL_SCANCODE_D))
        moveRight();
    else if(!input.isKeyHeld(SDL_SCANCODE_A) && !input.isKeyHeld(SDL_SCANCODE_D))
        stopMoving();

    // Up - Down
    if(input.isKeyHeld(SDL_SCANCODE_W) && input.isKeyHeld(SDL_SCANCODE_S))
        stopMoving();
    else if(input.isKeyHeld(SDL_SCANCODE_W))
        moveUp();
    else if(input.isKeyHeld(SDL_SCANCODE_S))
        moveDown();
    else if(!input.isKeyHeld(SDL_SCANCODE_W) && !input.isKeyHeld(SDL_SCANCODE_S))
        stopMoving();
}

