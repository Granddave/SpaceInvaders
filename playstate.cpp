#include "playstate.h"
#include "pausestate.h"
#include <iostream>

PlayState PlayState::m_PlayState;

void PlayState::init(Graphics *graphics)
{
    m_Graphics = graphics;

    m_Player = new Player(m_Graphics); // Make a smart pointer
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
    m_Player->update(ms);
}

void PlayState::draw()
{
    m_Player->draw(m_Graphics);
}
