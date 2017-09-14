#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class LTexture
{
public:
    LTexture();
    ~LTexture();

    bool loadFromFile(std::string path);
#ifdef _SDL_TTF_H
    bool loadFromRenderedText(std::string textureText,
                              TTF_Font *font,
                              SDL_Color textColor);
#endif
    void free();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);

    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
                SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int getWidth();
    int getHeight();

    void setRenderer(SDL_Renderer *Renderer);

private:
    SDL_Texture* m_Texture;
    SDL_Renderer* m_Renderer;
    int m_Width;
    int m_Height;
};

#endif // LTEXTURE_H
