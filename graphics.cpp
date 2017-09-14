#include "graphics.h"
#include <globals.h>

#include <iostream>
#include <SDL_ttf.h>
#include <SDL_image.h>

Graphics::Graphics()
{

}

Graphics::~Graphics()
{
    // Todo: delete SpriteSheets
    /*
    for (auto const &x : m_SpriteSheets)
    {
        delete x.second;
    }
    */


    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    m_Renderer = NULL;
    m_Window = NULL;

    TTF_Quit();
    IMG_Quit();
}

bool Graphics::init()
{
    bool success = true;

    Uint32 windowFlags;
#if FULLSCREEN
    windowFlags = SDL_WINDOW_FULLSCREEN;
#else
    windowFlags = SDL_WINDOW_SHOWN;
#endif
    m_Window = SDL_CreateWindow(globals::WINDOW_TITLE.c_str(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                globals::SCREEN_WIDTH,
                                globals::SCREEN_HEIGHT,
                                windowFlags);
    if(m_Window == NULL)
    {
        std::cout << "Window could not be created!"
                  << "SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        Uint32 renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        m_Renderer = SDL_CreateRenderer(m_Window, -1, renderFlags);

        if(m_Renderer == NULL)
        {
            std::cout << "Renderer could not be created!"
                      << "SDL_Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0xFF);

            // Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags))
            {
                std::cout << "SDL_image could not initialize! "
                          << "SDL_Error: " << IMG_GetError() << std::endl;
                success = false;
            }

            if(TTF_Init() == -1)
            {
                std::cout << "SDL_ttf could not initialized! "
                          << "TTF_Error: " << TTF_GetError() << std::endl;
                success = false;
            }
        }
    }
    return success;
}

SDL_Surface *Graphics::loadImage(const std::string &filePath)
{
    if(m_SpriteSheets.count(filePath) == 0)
    {
        m_SpriteSheets[filePath] = IMG_Load(filePath.c_str());

        SDL_SetColorKey(m_SpriteSheets[filePath], SDL_TRUE,
                        SDL_MapRGB(m_SpriteSheets[filePath]->format,
                                   0, 0x80, 0xFF));
    }
    return m_SpriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture,
                           SDL_Rect* srcRect,
                           SDL_Rect* destRect)
{
    SDL_RenderCopy(m_Renderer, texture, srcRect, destRect);
}

void Graphics::flip()
{
    SDL_RenderPresent(m_Renderer);
}

void Graphics::clear()
{
    SDL_RenderClear(m_Renderer);
}

SDL_Renderer *Graphics::getRenderer() const
{
    return m_Renderer;
}
