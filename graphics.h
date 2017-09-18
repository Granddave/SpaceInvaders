#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <map>
#include <memory>
#include <string>

#include "sprite.h"

class Graphics
{
public:
    Graphics();
    ~Graphics();

    bool init();

    SDL_Texture* loadTexture(const std::string &filePath);

    void blitSurface(SDL_Texture* texture,
                     SDL_Rect* srcRect,
                     SDL_Rect* destRect);
    void flip();
    void clear();

    SDL_Renderer* getRenderer() const;
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

    std::map<std::string, SDL_Texture*> m_SpriteSheets;
};

#endif // GRAPHICS_H
