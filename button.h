#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include "graphics.h"
#include <string.h>

class Button
{
public:
    Button(const std::string text, int x, int y, int w, int h);

    void setRect(const SDL_Rect& rect);
    void setText(const char* text);
    SDL_Rect rect();
    int state();

    void handleEvents(SDL_Event &e);
    void draw(Graphics* graphics);

    enum buttonState
    {
        BUTTON_MOUSE_OUT = 0,
        BUTTON_MOUSE_OVER_MOTION,
        BUTTON_MOUSE_DOWN,
        BUTTON_MOUSE_UP
    };
private:
    std::string m_Text;
    SDL_Rect m_Rect;
    Uint8 m_Alpha;
    buttonState m_State;
};

#endif // BUTTON_H
