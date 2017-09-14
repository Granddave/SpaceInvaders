#include "menustate.h"
#include "playstate.h"
#include <iostream>

MenuState MenuState::m_MenuState;

void MenuState::init(Graphics* graphics)
{
    m_Graphics = graphics;
    m_Button = new Button(100, 100, 150, 100);
}

void MenuState::clean()
{
    delete m_Button;
}

void MenuState::pause()
{
    std::cout << "Menu state paused" << std::endl;
}

void MenuState::resume()
{
    std::cout << "Menu state resumed" << std::endl;
}

void MenuState::handleEvents(Game *game)
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

    m_Button->handleEvents(event);

    if(m_Button->state() == Button::BUTTON_MOUSE_DOWN)
        game->changeState(PlayState::instance());
    else if(m_Input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
        game->quit();
}

void MenuState::update(Game *game, int ms)
{
    (void) game;
    (void) ms;
#if 0
    SDL_Rect temp = m_Button->rect();
    temp.x += 1 * ms;
    m_Button->setRect(temp);
#endif
}

void MenuState::draw(Graphics &graphics)
{
    m_Button->draw(graphics);
}
