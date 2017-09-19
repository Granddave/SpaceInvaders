#include "menustate.h"
#include "playstate.h"
#include <iostream>

MenuState MenuState::m_MenuState;

void MenuState::init(Graphics* graphics)
{
    m_Graphics = graphics;
    const int num = 2;
    const int w = 200 * globals::MENU_SCALE;
    const int h = 50 * globals::MENU_SCALE;
    const int padding = 20 * globals::MENU_SCALE; // Height space

    for(int i = 0; i < num; i++)
    {
        m_Buttons.push_back(new Button("",
                                       globals::SCREEN_WIDTH / 2 - w / 2,
                                       (globals::SCREEN_HEIGHT / 2 - ((num) * h + (num - 1) * padding) / 2)
                                       + i * h + padding * i,
                                       w, h));
    }
    m_Buttons[0]->setText("Start game");
    m_Buttons[1]->setText("Exit");
}

void MenuState::clean()
{
    for(auto const& b: m_Buttons)
         delete b;
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

    for(auto const& b: m_Buttons)
        b->handleEvents(event);

    if(m_Buttons[0]->state() == Button::BUTTON_MOUSE_DOWN)
        game->changeState(PlayState::instance());
    if(m_Buttons[1]->state() == Button::BUTTON_MOUSE_DOWN)
        game->quit();

    if(m_Input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
        game->quit();
}

void MenuState::update(Game *game, int ms)
{
    (void) game;
    (void) ms;
}

void MenuState::draw()
{
    for(auto const& b: m_Buttons)
         b->draw(m_Graphics);
}
