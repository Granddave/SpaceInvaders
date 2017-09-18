#include "sprite.h"
#include "graphics.h"
#include "globals.h"

#include <string>
#include <iostream>

Sprite::Sprite()
{

}

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

Sprite::~Sprite()
{

}

void Sprite::update()
{

}

void Sprite::draw(Graphics* graphics, int x, int y)
{
    SDL_Rect destRect = {x, y,
                         m_SrcRect.w * globals::PIXEL_SCALE,
                         m_SrcRect.h * globals::PIXEL_SCALE};

    graphics->blitSurface(m_SpriteSheet, &m_SrcRect, &destRect);
}

SDL_Rect Sprite::getRect()
{
    return m_SrcRect;
}

