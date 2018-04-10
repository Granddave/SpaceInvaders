#ifndef SPRITE_H
#define SPRITE_H


#include <SDL2/SDL.h>
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
    SDL_Rect getRect();

private:
    SDL_Rect m_SrcRect;
    SDL_Texture* m_SpriteSheet;
};

#endif // SPRITE_H
