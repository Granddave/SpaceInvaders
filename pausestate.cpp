#include "pausestate.h"
#include "playstate.h"
#include <iostream>

PauseState PauseState::m_PauseState;

void PauseState::init(Graphics* graphics)
{
    m_Graphics = graphics;
}

void PauseState::clean()
{

}

void PauseState::pause()
{
    std::cout << "Pause state paused" << std::endl;
}

void PauseState::resume()
{
    std::cout << "Pause state resumed" << std::endl;
}

void PauseState::handleEvents(Game *game)
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

        default:
        break;
        }
    }

    if(m_Input.wasKeyPressed(SDL_SCANCODE_P))
        game->popState();
    else if(m_Input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
        game->quit();

}

void PauseState::update(Game *game, int ms)
{
    (void) game;
    (void) ms;

}

void PauseState::draw(Graphics &graphics)
{
    (void) graphics;

}
