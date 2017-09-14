#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include "graphics.h"

enum buttonState
{
    BUTTON_MOUSE_OUT = 0,
    BUTTON_MOUSE_OVER_MOTION,
    BUTTON_MOUSE_DOWN,
    BUTTON_MOUSE_UP
};

class Button
{
public:
    Button(int x, int y, int w, int h);

    void setRect(const SDL_Rect& rect);

    void handleEvents(SDL_Event &e);
    void draw(Graphics& graphics);

private:
    SDL_Rect m_Rect;
    Uint8 m_Alpha;
    buttonState m_State;
};

#endif // BUTTON_H
