#include "ltexture.h"

#include <iostream>

LTexture::LTexture()
    : m_Texture(NULL), m_Width(0), m_Height(0)
{

}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile(std::string path)
{
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        std::cout << "Unable to load image"
                  << path
                  << "SDL_image Error: "
                  << IMG_GetError()
                  << std::endl;
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF ));

        newTexture = SDL_CreateTextureFromSurface(m_Renderer, loadedSurface);
        if(newTexture == NULL)
        {
            std::cout << "Unable to create texture from "
                      << path
                      << "SDL Error: "
                      << SDL_GetError()
                      << std::endl;
        }
        else
        {
            // Get dimensions
            m_Width = loadedSurface->w;
            m_Height = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    m_Texture = newTexture;
    return m_Texture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string textureText,
                                    TTF_Font* font,
                                    SDL_Color textColor)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font,
                                                    textureText.c_str(),
                                                    textColor);

    if(textSurface == NULL)
    {
        std::cout << "Unable to render text surface! "
                  << "SDL_ttf error: "
                  << TTF_GetError()
                  << std::endl;
    }
    else
    {
        m_Texture = SDL_CreateTextureFromSurface(m_Renderer, textSurface);
        if(m_Texture == NULL)
        {
            std::cout << "Unable to create text from rendered text! "
                      << "SDL error: "
                      << SDL_GetError()
                      << std::endl;
        }
        else
        {
            m_Width = textSurface->w;
            m_Height = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }

    return m_Texture != NULL;
}
#endif

void LTexture::free()
{
    if (m_Texture != NULL)
    {
        SDL_DestroyTexture(m_Texture);
        m_Texture = NULL;
        m_Width = 0;
        m_Height = 0;
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(m_Texture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(m_Texture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(m_Texture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, m_Width, m_Height};

    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(m_Renderer, m_Texture, clip, &renderQuad,
                     angle, center, flip);
}

int LTexture::getWidth()
{
    return m_Width;
}

int LTexture::getHeight()
{
    return m_Height;
}

void LTexture::setRenderer(SDL_Renderer *Renderer)
{
    m_Renderer = Renderer;
}
