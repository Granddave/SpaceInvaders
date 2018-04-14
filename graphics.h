#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "sprite.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <memory>
#include <string>

class Graphics
{
public:
    Graphics();
    ~Graphics();

    bool init();

    SDL_Texture* loadTexture(const std::string &filePath);

    void blitSurface(SDL_Texture* texture,
                     const SDL_Rect* srcRect,
                     const SDL_Rect* destRect);

    void blitSurface(SDL_Texture* texture,
                     const SDL_Rect* srcRect,
                     const SDL_Rect* destRect,
                     const double angle,
                     const SDL_Point* center,
                     const SDL_RendererFlip flip);
    void flip();
    void clear();

    SDL_Renderer* getRenderer() const;

    static bool s_Fullscreen;
    static bool s_AcceleratedGraphics;
    static bool s_VSyncSDL;
    static int s_ScreenWidth;
    static int s_ScreenHeight;
    static float s_Scale;
    static int s_FPS;
    static int s_MaxFrameTime;
    static std::string s_WindowTitle;
    const std::string WINDOW_TITLE = "Space Invaders";

private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

    std::map<std::string, SDL_Surface*> m_SpriteSheets;
};

#endif // GRAPHICS_H
