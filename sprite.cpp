#include "sprite.h"
#include "graphics.h"
#include "globals.h"

#include <string>
#include <iostream>

Sprite::Sprite(Graphics* graphics, const std::string& filePath,
               int srcX, int srcY, int width, int height)
    : m_SrcRect({srcX, srcY, width, height})
{
    m_SpriteSheet = graphics->loadTexture(filePath);
    if(m_SpriteSheet == NULL)
    {
        std::cout << "Unable to optimize image " << filePath
                  << "SDL_Error: " << SDL_GetError()
                  << std::endl;
    }
}

void Sprite::draw(Graphics* graphics, const int x, const int y, const float scale)
{
    SDL_Rect destRect = {x, y,
                         m_SrcRect.w * scale * Graphics::s_Scale,
                         m_SrcRect.h * scale * Graphics::s_Scale};

    graphics->blitSurface(m_SpriteSheet, &m_SrcRect, &destRect);
}

void Sprite::draw(Graphics *graphics, int x, int y, const double angle,
                  const SDL_Point *center, const SDL_RendererFlip flip,
                  float scale)
{
    SDL_Rect destRect = {x, y,
                         m_SrcRect.w * scale * Graphics::s_Scale,
                         m_SrcRect.h * scale * Graphics::s_Scale};

    graphics->blitSurface(m_SpriteSheet, &m_SrcRect, &destRect, angle, center,
                          flip);
}

SDL_Rect Sprite::getRect()
{
    return m_SrcRect;
}
