#include "game.h"
#include "input.h"
#include "timer.h"
#include "globals.h"
#include <iostream>
#include <algorithm>

Game::Game()
{

}

namespace {
    const int FPS = 60;
    const int MAX_FRAME_TIME = 1000 / FPS;
}

bool Game::run()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize!"
                  << "SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    Graphics graphics;
    if(!graphics.init())
    {
        std::cout << "Could not initialize graphics module!" << std::endl;
        return false;
    }

    Input input;
    SDL_Event event;
    Timer fpsTimer;
    Timer capTimer;
    int countedFrames = 0;
    fpsTimer.start();

    bool quit = false;
#if VSYNC
    int LAST_UPDATE_TIME = SDL_GetTicks();
#endif
    m_Player = new Player (graphics, "resources/spaceinvaders.png",
                           50, 2, 13, 10, 0, 0, Vec2f::zero());
    m_Button = new Button(100, 100, 150, 100);

    // Main game loop
    while(!quit)
    {
        capTimer.start();
        input.beginNewFrame();

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                quit = true;
            break;

            case SDL_KEYDOWN:
                if(event.key.repeat == 0)
                {
                    input.keyDownEvent(event);
                }
            break;

            case SDL_KEYUP:
                input.keyUpEvent(event);
            break;

            default:
            break;
            }
        }

        if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
            quit = true;

        m_Player->handleInput(input);
        m_Button->handleEvents(event);

        // Graphics
#if VSYNC
        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        LAST_UPDATE_TIME = CURRENT_TIME_MS;

        std::cout << "FPS: " << 1000 / (ELAPSED_TIME_MS + 1)  << "\n";
        update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
#else
        float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
        if(avgFPS > 100)
            avgFPS = 0;

        //std::cout << "avg FPS: " << avgFPS << "\n";
        countedFrames++;

        update(std::min((int)fpsTimer.getTicks(), MAX_FRAME_TIME));
#endif
        draw(graphics);

        int frameTicks = capTimer.getTicks();
        if(frameTicks < MAX_FRAME_TIME)
            SDL_Delay(MAX_FRAME_TIME - frameTicks);
    }
    return 0;
}

void Game::update(float ms)
{
    m_Player->update(ms);
    // Get button states
}

void Game::draw(Graphics &graphics)
{
    graphics.clear();

    m_Player->draw(graphics);
    m_Button->draw(graphics);

    graphics.flip();
}

void Game::close()
{
    SDL_Quit();
}
