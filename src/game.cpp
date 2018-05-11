#include "game.h"
#include "utils/input.h"
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

    // Todo: Wrap in audio class
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

    tickTimer.start();
    updateTimer.start();
    capTimer.start();

    while(running())
    {
        handleEvents();
        update();
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

void Game::update()
{
    int lastFrameTime = std::min((int)updateTimer.restart(), Graphics::s_MaxFrameTime);
    if(tickTimer.getTicks() >= 1000)
    {
        std::cout << "Current Ms: "<< lastFrameTime << "\n";

        if (globals::printFPS)
            std::cout << "Current FPS: "<< m_Fps.getFps() << "\n";
        tickTimer.restart();
    }

    m_Fps.newFrame();
    m_States.back()->update(this, lastFrameTime);
}

void Game::draw()
{
    m_Graphics.clear();
    m_States.back()->draw();
    // Place FPS rendering here?
    m_Graphics.flip();

    if (!Graphics::s_VSyncSDL && (uint32)Graphics::s_MaxFrameTime > capTimer.getTicks())
    {
        uint32 delay = Graphics::s_MaxFrameTime - capTimer.getTicks();
        SDL_Delay(delay);
    }
    capTimer.restart();
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
