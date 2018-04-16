#include "texturemanager.h"
#include "graphics/sprite.h"

#include <iostream>

TextureManager* TextureManager::m_Instance = 0;

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
    for (auto it = m_SpriteSheets.begin(); it != m_SpriteSheets.end(); ++it)
    {
        SDL_DestroyTexture(it->second);
    }
    m_SpriteSheets.clear();
}

bool TextureManager::loadTexture(SDL_Renderer *renderer, const std::string &filePath)
{
    bool success = true;
    if(m_SpriteSheets.count(filePath) == 0)
    {
        SDL_Surface* surface= IMG_Load(filePath.c_str());

        if (surface == NULL)
        {
            std::cout << "Could not load texture: " << filePath << "\n"
                      << "IMG_Error: " << IMG_GetError() << std::endl;
            success = false;
        }

        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0x80, 0xFF));
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if(texture == NULL)
        {
            std::cout << "Unable to load image " << filePath
                      << "SDL_Error: " << SDL_GetError()
                      << std::endl;
            success = false;
        }
        m_SpriteSheets[filePath] = texture;
    }
    return success;
}

SDL_Texture* TextureManager::getTexture(const std::string& filepath)
{
    return m_SpriteSheets[filepath];
}

