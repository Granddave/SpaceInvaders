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
        std::cout << "Unable to load image " << filePath
                  << "SDL_Error: " << SDL_GetError()
                  << std::endl;
    }
}

void Sprite::draw(Graphics* graphics, const int x, const int y, const float scale)
{
    SDL_Rect destRect = getDestRect(x, y, scale);
    graphics->blitSurface(m_SpriteSheet, &m_SrcRect, &destRect);
}

void Sprite::draw(Graphics *graphics, int x, int y, const double angle,
                  const SDL_Point *center, const SDL_RendererFlip flip,
                  float scale)
{
    SDL_Rect destRect = getDestRect(x, y, scale);
    graphics->blitSurface(m_SpriteSheet, &m_SrcRect, &destRect,
                          angle, center, flip);
}

SDL_Rect Sprite::getRect() const
{
    return m_SrcRect;
}

SDL_Rect Sprite::getDestRect(int x, int y, float scale)
{
    return {x, y, (int)(m_SrcRect.w * scale * Graphics::s_Scale),
                  (int)(m_SrcRect.h * scale * Graphics::s_Scale)};
}
