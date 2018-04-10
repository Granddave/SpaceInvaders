#include "graphics.h"
#include <globals.h>

#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

static const int INIT_SCREEN_WIDTH = 1280;
static const int INIT_SCREEN_HEIGHT = 720;

bool Graphics::s_Fullscreen = false;
bool Graphics::s_AcceleratedGraphics = true;
bool Graphics::s_VSyncSDL = true;
int Graphics::s_ScreenWidth = INIT_SCREEN_WIDTH;
int Graphics::s_ScreenHeight = INIT_SCREEN_HEIGHT;
float Graphics::s_Scale = 1.0f;
int Graphics::s_FPS = 60;
int Graphics::s_MaxFrameTime = 1000 / Graphics::s_FPS;
std::string Graphics::s_WindowTitle = "Space Invaders";

Graphics::Graphics()
{
    if(s_Fullscreen)
    {
        s_ScreenWidth = 1920;
        s_ScreenHeight = 1080;
    }
    else
    {
        s_ScreenWidth = 1280;
        s_ScreenHeight = 720;
    }
    s_Scale *= (float)(s_ScreenWidth) / (float)(INIT_SCREEN_WIDTH);
}

Graphics::~Graphics()
{
    // Todo: delete SpriteSheets
    for (auto it = m_SpriteSheets.begin(); it != m_SpriteSheets.end(); ++it)
    {
        SDL_FreeSurface(it->second);
    }
    m_SpriteSheets.clear();

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

    SDL_DisplayMode displayMode;

    int displayInUse = 0; // Current display
    int numDisplayModes = SDL_GetNumDisplayModes(displayInUse);
    if (numDisplayModes < 1)
    {
        std::cout << "Could not get number of display modes! "
                  << "SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    std::cout << "Number of display modes: " << numDisplayModes << std::endl;

    SDL_GetDesktopDisplayMode(0, &displayMode);
    std::cout << displayMode.w << "x" << displayMode.h << '\n';

    /*
    for(int i = 0; i < numDisplayModes; i++)
    {
        if(SDL_GetDisplayMode(displayInUse, i, &m_DisplayMode) != 0)
        {
            std::cout << "Get display mode failed! "
                      << "SDL_Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        std::cout << m_DisplayMode.w << "x" << m_DisplayMode.h << '\n';
    }
    */


    Uint32 windowFlags = s_Fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;

    m_Window = SDL_CreateWindow(Graphics::s_WindowTitle.c_str(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                Graphics::s_ScreenWidth, Graphics::s_ScreenHeight,
                                windowFlags);
    if(m_Window == NULL)
    {
        std::cout << "Window could not be created!\n"
                  << "SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        Uint32 renderFlags = 0;
        if(Graphics::s_AcceleratedGraphics)
            renderFlags = renderFlags | SDL_RENDERER_ACCELERATED;
        else
            renderFlags = renderFlags | SDL_RENDERER_SOFTWARE;

        if(Graphics::s_VSyncSDL && Graphics::s_AcceleratedGraphics)
            renderFlags = renderFlags | SDL_RENDERER_PRESENTVSYNC;

        m_Renderer = SDL_CreateRenderer(m_Window, -1, renderFlags);

        if(m_Renderer == NULL)
        {
            std::cout << "Renderer could not be created!\n"
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
                std::cout << "SDL_image could not initialize!\n"
                          << "SDL_Error: " << IMG_GetError() << std::endl;
                success = false;
            }

            if(TTF_Init() == -1)
            {
                std::cout << "SDL_ttf could not initialized!\n"
                          << "TTF_Error: " << TTF_GetError() << std::endl;
                success = false;
            }
        }
    }
    return success;
}

SDL_Texture* Graphics::loadTexture(const std::string &filePath)
{
    // Todo: https://github.com/gonccalo/SDL-Game/blob/master/SDL-Game/TextureManager.cpp
    if(m_SpriteSheets.count(filePath) == 0)
    {
        m_SpriteSheets[filePath] = IMG_Load(filePath.c_str());

        if (m_SpriteSheets[filePath] == NULL)
        {
            std::cout << "Could not load texture: " << filePath << "\n"
                      << "IMG_Error: " << IMG_GetError() << std::endl;
        }

        SDL_SetColorKey(m_SpriteSheets[filePath], SDL_TRUE,
                        SDL_MapRGB(m_SpriteSheets[filePath]->format,
                                   0, 0x80, 0xFF));
    }

    return SDL_CreateTextureFromSurface(m_Renderer, m_SpriteSheets[filePath]);
}

void Graphics::blitSurface(SDL_Texture* texture,
                           const SDL_Rect* srcRect,
                           const SDL_Rect* destRect)
{
    SDL_RenderCopy(m_Renderer, texture, srcRect, destRect);
}

void Graphics::blitSurface(SDL_Texture* texture,
                           const SDL_Rect* srcRect,
                           const SDL_Rect* destRect,
                           const double angle,
                           const SDL_Point *center,
                           const SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(m_Renderer, texture, srcRect, destRect, angle, center, flip);
}

void Graphics::flip()
{
    SDL_RenderPresent(m_Renderer);
}

void Graphics::clear()
{
    SDL_RenderClear(m_Renderer);
}

SDL_Renderer* Graphics::getRenderer() const
{
    return m_Renderer;
}
