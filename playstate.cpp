#include "playstate.h"
#include "pausestate.h"
#include <iostream>

PlayState PlayState::m_PlayState;

void PlayState::init(Graphics *graphics)
{
    m_Graphics = graphics;

    m_Player = new Player(m_Graphics);
    m_PlayerBullets.reserve(2);
}

void PlayState::clean()
{
    delete m_Player;
}

void PlayState::pause()
{
    std::cout << "Play state paused" << std::endl;
}

void PlayState::resume()
{
    std::cout << "Play state resumed" << std::endl;
    m_Input.clearAll();
}

void PlayState::handleEvents(Game *game)
{
    SDL_Event event;
    m_Input.beginNewFrame();
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            game->quit();
        break;

        case SDL_KEYDOWN:
            if(event.key.repeat == 0)
            {
                m_Input.keyDownEvent(event);
            }
        break;

        case SDL_KEYUP:
            m_Input.keyUpEvent(event);
        break;

        case SDL_MOUSEBUTTONDOWN:
            m_Input.mouseDownEvent(event);
        break;

        case SDL_MOUSEBUTTONUP:
            m_Input.mouseUpEvent(event);
        break;

        default:
        break;
        }
    }

    if(m_Input.wasKeyPressed(SDL_SCANCODE_P))
        game->pushState(PauseState::instance());
    else if(m_Input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
        game->quit();

    m_Player->handleInput(m_Input);
}

void PlayState::update(Game *game, int ms)
{
    (void) game;

    // Bullets
    for(Bullet& b: m_PlayerBullets)
        b.update(ms);
    if (m_Player->isShooting())
    {
        Vec2f pos = m_Player->shootingPos();
        m_PlayerBullets.emplace_back(m_Graphics, pos.x, pos.y, m_Player->damage(),
                                     m_Player->shootingVec());
    }
    for(size_t i = 0; i < m_PlayerBullets.size(); i++)
    {
        if (m_PlayerBullets.at(i).deleteLater())
        {
            m_PlayerBullets.erase(m_PlayerBullets.begin() + i);
            std::cout << "Bullets: " << m_PlayerBullets.size() << std::endl;
        }
    }

    // Player
    m_Player->update(ms);
}

void PlayState::draw()
{
    m_Player->draw(m_Graphics);

    for(Bullet& b: m_PlayerBullets)
        b.draw(m_Graphics);
}
