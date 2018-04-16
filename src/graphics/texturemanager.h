#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

class TextureManager
{
public:
    static TextureManager* I()
    {
        if (instance == nullptr) { instance = new TextureManager(); }
        return instance;
    }
    ~TextureManager();

    bool loadTexture(SDL_Renderer* renderer, const std::string &filePath);
    SDL_Texture* getTexture(const std::string& filepath);

private:
    TextureManager();
    static TextureManager* instance;

    std::map<std::string, SDL_Texture*> m_SpriteSheets;
};

#endif // TEXTUREMANAGER_H
