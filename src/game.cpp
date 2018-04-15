#include "game.h"
#include "utils/input.h"
#include "utils/timer.h"
#include "utils/globals.h"
#include "states/gamestate.h"
#include "states/menustate.h"

#include <iostream>
#include <algorithm>
#include <SDL2/SDL_mixer.h>

Game::Game()
{

}

bool Game::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize!"
                  << "SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if(!m_Graphics.init())
    {
        std::cout << "Could not initialize graphics module!" << std::endl;
        return false;
    }

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return false;
    }

    m_Running = true;
    std::cout << "Game is initialized successfully" << std::endl;

    return true;
}

void Game::exec()
{
    changeState(MenuState::instance());

    bool printFPS = false;
    Timer secondTimer;
    if (printFPS)
        secondTimer.start();

    Timer updateTimer;
    updateTimer.start();
    while(running())
    {
        handleEvents();

        if(printFPS && secondTimer.getTicks() > 1000)
        {
            std::cout << "Current FPS: " << 1000 / (updateTimer.getTicks() + 1)  << "\n";
            secondTimer.restart();
        }
        update(std::min((int)updateTimer.getTicks(), Graphics::s_MaxFrameTime));
        updateTimer.restart();

        draw();
    }

    clean();
}

void Game::changeState(GameState *state)
{
    if(!m_States.empty())
    {
        m_States.back()->clean();
        m_States.pop_back();
    }

    m_States.push_back(state);
    m_States.back()->init(&m_Graphics);
}

void Game::pushState(GameState *state)
{
    if(!m_States.empty())
    {
        m_States.back()->pause();
    }

    m_States.push_back(state);
    m_States.back()->init(&m_Graphics);
}

void Game::popState()
{
    if(!m_States.empty())
    {
        m_States.back()->clean();
        m_States.pop_back();
    }
    if(!m_States.empty())
    {
        m_States.back()->resume();
    }
}

void Game::handleEvents()
{
    m_States.back()->handleEvents(this);
}

void Game::update(int ms)
{
    m_States.back()->update(this, ms);
}

void Game::draw()
{
    m_Graphics.clear();
    m_States.back()->draw();
    m_Graphics.flip();
}

void Game::clean()
{
    while(!m_States.empty())
    {
        m_States.back()->clean();
        m_States.pop_back();
    }
    Mix_CloseAudio();
    SDL_Quit();
}