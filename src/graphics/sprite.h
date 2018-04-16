#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <string>

class Graphics;

class Sprite
{
public:
    Sprite(Graphics* graphics, const std::string& filePath,
           int srcX, int srcY, int width, int height);

    void draw(Graphics* graphics, const int x, const int y, const float scale = 1.0f);
    void draw(Graphics* graphics, int x, int y, const double angle,
              const SDL_Point* center, const SDL_RendererFlip flip,
              float scale = 1.0f);
    SDL_Rect getRect() const;

private:
    SDL_Rect getDestRect(int x, int y, float scale);

    std::string m_FilePath;
    SDL_Rect m_SrcRect;
};

#endif // SPRITE_H
