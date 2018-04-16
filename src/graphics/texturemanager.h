#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

class TextureManager
{
public:
    static TextureManager* instance()
    {
        if (m_Instance == nullptr) { m_Instance = new TextureManager(); }
        return m_Instance;
    }
    ~TextureManager();

    bool loadTexture(SDL_Renderer* renderer, const std::string &filePath);
    SDL_Texture* getTexture(const std::string& filepath);

private:
    TextureManager();
    static TextureManager* m_Instance;

    std::map<std::string, SDL_Texture*> m_SpriteSheets;
};

#endif // TEXTUREMANAGER_H
