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
    : Entity(graphics, "resources/spaceinvaders.png", 51, 3, 11, 8,
             posX, posY, Vec2f::zero()),
      m_ShootCooldown(0.0f),
      m_ShootVec({0, 0}),
      m_isShooting(false),
      m_DamageBase(c_PlayerShootDamage),
      m_DamageMultiplier(1)
{
    setPos(Graphics::s_ScreenWidth / 2 -
               (getSize().x * c_PlayerScale * Graphics::s_Scale) / 2,
           Graphics::s_ScreenHeight* 0.9f);

    m_ShootPos = {(m_Sprite.getRect().w* Graphics::s_Scale * c_PlayerScale) / 2, 0 };

    m_Graphics = graphics;
    m_ShootSound = Mix_LoadWAV("resources/shoot.wav");
}

Player::~Player()
{
    Mix_FreeChunk(m_ShootSound);
}

void Player::update(int ms)
{
    // ---- Movement ----
    // Update velocity
    if(std::abs(m_Velocity.x) < c_PlayerBaseVel && std::abs(m_Acceleration.x) > 0)
        m_Velocity.x += m_Acceleration.x * ms;
    if(std::abs(m_Velocity.y) < c_PlayerBaseVel && std::abs(m_Acceleration.y) > 0)
        m_Velocity.y += m_Acceleration.y * ms;

    // Update position
    m_Pos.x += m_Velocity.x * ms * Graphics::s_Scale;
    m_Pos.y += m_Velocity.y * ms * Graphics::s_Scale;

    // Add friction
    m_Velocity.x = (std::abs(m_Velocity.x) > 0.001) ? (m_Velocity.x * 0.9f) : 0;
    m_Velocity.y = (std::abs(m_Velocity.y) > 0.001) ? (m_Velocity.y * 0.9f) : 0;

    checkBorderCollision();

    // ---- Shooting ----
    m_isShooting = false;
    m_ShootCooldown = m_ShootCooldown > 0.0f ? m_ShootCooldown - ms : 0.0f;
}

void Player::draw(Graphics* graphics)
{
    if(m_Alive)
        m_Sprite.draw(graphics, m_Pos.x, m_Pos.y, c_PlayerScale);
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
    if(m_Pos.x <= 0)
    {
        m_Pos.x = 0;
        m_Velocity.x = 0;
    }
    if(m_Pos.x + m_Sprite.getRect().w * c_PlayerScale >= Graphics::s_ScreenWidth)
    {
        m_Pos.x = Graphics::s_ScreenWidth - m_Sprite.getRect().w * c_PlayerScale;
        m_Velocity.x = 0;
    }
    if(m_Pos.y <= 0)
    {
        m_Pos.y = 0;
        m_Velocity.y = 0;
    }
    if(m_Pos.y + m_Sprite.getRect().h * c_PlayerScale >= Graphics::s_ScreenHeight)
    {
        m_Pos.y = Graphics::s_ScreenHeight - m_Sprite.getRect().h * c_PlayerScale;
        m_Velocity.y = 0;
    }
}

void Player::calcMovement(Input &input)
{
    // Left - Right
    if(input.isKeyHeld(SDL_SCANCODE_A) && input.isKeyHeld(SDL_SCANCODE_D))
        m_Acceleration.x = 0;
    else if(input.isKeyHeld(SDL_SCANCODE_A))
        m_Acceleration.x = -c_PlayerAcceleration;
    else if(input.isKeyHeld(SDL_SCANCODE_D))
        m_Acceleration.x = c_PlayerAcceleration;
    else if(!input.isKeyHeld(SDL_SCANCODE_A) && !input.isKeyHeld(SDL_SCANCODE_D))
        m_Acceleration.x = 0;

    // Up - Down
    if(input.isKeyHeld(SDL_SCANCODE_W) && input.isKeyHeld(SDL_SCANCODE_S))
        m_Acceleration.y = 0;
    else if(input.isKeyHeld(SDL_SCANCODE_W))
        m_Acceleration.y = -c_PlayerAcceleration;
    else if(input.isKeyHeld(SDL_SCANCODE_S))
        m_Acceleration.y = c_PlayerAcceleration;
    else if(!input.isKeyHeld(SDL_SCANCODE_W) && !input.isKeyHeld(SDL_SCANCODE_S))
        m_Acceleration.y = 0;
}

bool Player::checkIfShoot(Input &input)
{
    return (input.isKeyHeld(SDL_SCANCODE_SPACE) || input.isButtonHeld(SDL_BUTTON_LEFT))
            && m_ShootCooldown == 0.0f;
}

void Player::calcShootingVec()
{
    Vec2 mousePos;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    m_ShootVec.x = mousePos.x - (m_Pos.x + m_ShootPos.x);
    m_ShootVec.y = mousePos.y - (m_Pos.y + m_ShootPos.y);
    m_ShootVec.normalize();
    m_ShootVec.x = m_ShootVec.x * c_PlayerShootVelocity; // Todo: Refactor
    m_ShootVec.y = m_ShootVec.y * c_PlayerShootVelocity;
}

void Player::playShootingSound()
{
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
