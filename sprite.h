#ifndef SPRITE_H
#define SPRITE_H


#include <SDL.h>
#include <string>

class Graphics;

class Sprite
{
public:
    Sprite();
    Sprite(Graphics* graphics, const std::string& filePath,
           int srcX, int srcY, int width, int height);

    virtual ~Sprite();
    virtual void update();

    void draw(Graphics* graphics, int x, int y);

    SDL_Rect getRect();

private:
    SDL_Rect m_SrcRect;
    SDL_Texture* m_SpriteSheet;

    float m_X, m_Y;
};

#endif // SPRITE_H
