#include "player.h"
#include <iostream>
#include <math.h>
#include <algorithm>

const float c_PlayerAcceleration = 0.01f;
const float c_PlayerBaseVel = 1.5f;
const float c_PlayerDampVel = c_PlayerBaseVel * 0.007f;
const float c_PlayerThreshholdSpeed = c_PlayerDampVel * 5.0f;
const float c_PlayerScale = 3.0f;
const float c_PlayerShootCooldown = 100.0f;
const float c_PlayerShootVelocity = 2.0f;

Player::Player(Graphics *graphics,
               float posX, float posY)
    : Entity(graphics, "resources/spaceinvaders.png", 51, 3, 11, 8,
             posX, posY, Vec2f::zero()),
      m_ShootCooldown(0.0f),
      m_ShootPos({5, 4})
{
    setPos(Graphics::s_ScreenWidth / 2 -
               (getSize().x * c_PlayerScale * Graphics::s_Scale) / 2,
           Graphics::s_ScreenHeight* 0.9f);
    m_Graphics = graphics;
    m_Bullets.reserve(2);
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

    // Check window borders
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

    // ---- Shooting ----
    for(Bullet& b: m_Bullets) // Todo: Move to PlayState!
        b.update(ms);

    if (m_ShootCooldown == c_PlayerShootCooldown)
        std::cout << "Shots alive: " << m_Bullets.size() << "\n";

    m_ShootCooldown = m_ShootCooldown > 0.0f ? m_ShootCooldown - ms : 0.0f;

    for(int i = 0; i < m_Bullets.size(); i++)
        if (m_Bullets.at(i).deleteLater())
            m_Bullets.erase(m_Bullets.begin() + i);
}

void Player::draw(Graphics* graphics)
{
    for(Bullet& b: m_Bullets) // Todo: Move to PlayState!
        b.draw(graphics);
    if(m_Alive)
        m_Sprite.draw(graphics, m_Pos.x, m_Pos.y, c_PlayerScale);
}

void Player::handleInput(Input &input)
{
    // ---- Movement ----
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

    // ---- Shooting ----
    if((input.isKeyHeld(SDL_SCANCODE_SPACE) || input.isButtonHeld(SDL_BUTTON_LEFT))
            && m_ShootCooldown == 0.0f)
    {
        m_ShootCooldown = c_PlayerShootCooldown;

        // Calculate shooting angle
        Vec2 mousePos;
        SDL_GetMouseState(&mousePos.x, &mousePos.y);
        Vec2f dir;
        dir.x = mousePos.x - (m_Pos.x + m_ShootPos.x);
        dir.y = mousePos.y - (m_Pos.y + m_ShootPos.y);
        float dirLen = sqrt(dir.x * dir.x + dir.y * dir.y);
        dir.x = dir.x / dirLen * c_PlayerShootVelocity;
        dir.y = dir.y / dirLen * c_PlayerShootVelocity;

        m_Bullets.emplace_back(m_Graphics,
                               getPos().x + (m_Sprite.getRect().w *
                                             Graphics::s_Scale *
                                             c_PlayerScale) / 2,
                               getPos().y, 10, dir);

        // Play shooting sound
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
}
