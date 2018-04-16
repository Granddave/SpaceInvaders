#include "player.h"

#include <iostream>
#include <math.h>
#include <algorithm>

const float c_PlayerAcceleration = 0.01f;
const float c_PlayerBaseVel = 1.0f;
const float c_PlayerDampVel = c_PlayerBaseVel * 0.007f;
const float c_PlayerThreshholdSpeed = c_PlayerDampVel * 5.0f;
const float c_PlayerScale = 3.0f;
const float c_PlayerShootCooldown = 100.0f;
const float c_PlayerShootVelocity = 0.8f; //2.0f;
const float c_PlayerShootDamage = 10.0f;

Player::Player(Graphics *graphics,
               float posX, float posY)
    : Entity(graphics, "res/spaceinvaders.png", 51, 3, 11, 8,
             posX, posY, Vector2::Zero()),
      m_ShootCooldown(0.0f),
      m_ShootVec({0, 0}),
      m_isShooting(false),
      m_DamageBase(c_PlayerShootDamage),
      m_DamageMultiplier(1)
{
    setPos(Graphics::s_ScreenWidth / 2 -
               (getSize().X * c_PlayerScale * Graphics::s_Scale) / 2,
           Graphics::s_ScreenHeight* 0.9f);

    m_ShootPos = {(m_Sprite.getRect().w* Graphics::s_Scale * c_PlayerScale) / 2, 0 };

    m_Graphics = graphics;
    m_ShootSound = Mix_LoadWAV("res/shoot.wav");
}

Player::~Player()
{
    Mix_FreeChunk(m_ShootSound);
}

void Player::update(int ms)
{
    // ---- Movement ----
    // Update velocity
    if(std::abs(m_Velocity.X) < c_PlayerBaseVel && std::abs(m_Acceleration.X) > 0)
        m_Velocity.X += m_Acceleration.X * ms;
    if(std::abs(m_Velocity.Y) < c_PlayerBaseVel && std::abs(m_Acceleration.Y) > 0)
        m_Velocity.Y += m_Acceleration.Y * ms;

    // Update position
    m_Pos += m_Velocity * ms * Graphics::s_Scale;

    // Add friction
    m_Velocity.X = (std::abs(m_Velocity.X) > 0.001) ? (m_Velocity.X * 0.9f) : 0;
    m_Velocity.Y = (std::abs(m_Velocity.Y) > 0.001) ? (m_Velocity.Y * 0.9f) : 0;

    checkBorderCollision();

    // ---- Shooting ----
    m_isShooting = false;
    m_ShootCooldown = m_ShootCooldown > 0.0f ? m_ShootCooldown - ms : 0.0f;
}

void Player::draw(Graphics* graphics)
{
    if(m_Alive)
        m_Sprite.draw(graphics, m_Pos.X, m_Pos.Y, c_PlayerScale);
}

void Player::handleInput(Input &input)
{
    calcMovement(input);

    if(checkIfShoot(input))
    {
        m_ShootCooldown = c_PlayerShootCooldown;
        m_isShooting = true;
        calcShootingVec();
        playShootingSound();
    }
}

void Player::checkBorderCollision()
{
    if(m_Pos.X <= 0)
    {
        m_Pos.X = 0;
        m_Velocity.X = 0;
    }
    if(m_Pos.X + m_Sprite.getRect().w * c_PlayerScale >= Graphics::s_ScreenWidth)
    {
        m_Pos.X = Graphics::s_ScreenWidth - m_Sprite.getRect().w * c_PlayerScale;
        m_Velocity.Y = 0;
    }
    if(m_Pos.Y <= 0)
    {
        m_Pos.Y = 0;
        m_Velocity.Y = 0;
    }
    if(m_Pos.Y + m_Sprite.getRect().h * c_PlayerScale >= Graphics::s_ScreenHeight)
    {
        m_Pos.Y = Graphics::s_ScreenHeight - m_Sprite.getRect().h * c_PlayerScale;
        m_Velocity.Y = 0;
    }
}

void Player::calcMovement(Input &input)
{
    // Left - Right
    if(input.isKeyHeld(SDL_SCANCODE_A) && input.isKeyHeld(SDL_SCANCODE_D))
        m_Acceleration.X = 0;
    else if(input.isKeyHeld(SDL_SCANCODE_A))
        m_Acceleration.X = -c_PlayerAcceleration;
    else if(input.isKeyHeld(SDL_SCANCODE_D))
        m_Acceleration.X = c_PlayerAcceleration;
    else if(!input.isKeyHeld(SDL_SCANCODE_A) && !input.isKeyHeld(SDL_SCANCODE_D))
        m_Acceleration.X = 0;

    // Up - Down
    if(input.isKeyHeld(SDL_SCANCODE_W) && input.isKeyHeld(SDL_SCANCODE_S))
        m_Acceleration.Y = 0;
    else if(input.isKeyHeld(SDL_SCANCODE_W))
        m_Acceleration.Y = -c_PlayerAcceleration;
    else if(input.isKeyHeld(SDL_SCANCODE_S))
        m_Acceleration.Y = c_PlayerAcceleration;
    else if(!input.isKeyHeld(SDL_SCANCODE_W) && !input.isKeyHeld(SDL_SCANCODE_S))
        m_Acceleration.Y = 0;
}

bool Player::checkIfShoot(Input &input)
{
    return (input.isKeyHeld(SDL_SCANCODE_SPACE) || input.isButtonHeld(SDL_BUTTON_LEFT))
            && m_ShootCooldown == 0.0f;
}

void Player::calcShootingVec()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    Vector2 mousePos(x, y);
    m_ShootVec = mousePos - (m_Pos + m_ShootPos);

    m_ShootVec = Vector2::Normalized(m_ShootVec) * c_PlayerShootVelocity;
}

void Player::playShootingSound()
{
    // Todo: Wrap in class:
    if(globals::sounds)
    {
        if(Mix_PlayChannel(-1, m_ShootSound, 0) == -1)
        {
            std::cerr << "Could not play sound: m_ShootSound ";
            if (m_ShootSound == NULL)
                std::cerr << "- I'ts NULL!";
            std::cerr << std::endl;
        }
    }
}
