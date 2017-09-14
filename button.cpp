#include "button.h"
#include <iostream>
Button::Button(int x, int y, int w, int h)
    : m_Rect({x, y, w, h}), m_Alpha(10), m_State(BUTTON_MOUSE_OUT)
{

}

void Button::setRect(const SDL_Rect &rect)
{
    m_Rect = rect;
}

void Button::handleEvents(SDL_Event& e)
{
    if(e.type == SDL_MOUSEMOTION ||
       e.type == SDL_MOUSEBUTTONDOWN ||
       e.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        std::cout << x << ", " << y << "\n";

        bool inside = true;

        if(x < m_Rect.x)
        {
            inside = false;
        }
        else if(x > m_Rect.x + m_Rect.w)
        {
            inside = false;
        }
        else if(y < m_Rect.y)
        {
            inside = false;
        }
        else if(y > m_Rect.y + m_Rect.h)
        {
            inside = false;
        }

        if(!inside)
        {
            m_State = BUTTON_MOUSE_OUT;
        }
        else
        {
            switch(e.type)
            {
            case SDL_MOUSEMOTION:
                m_State = BUTTON_MOUSE_OVER_MOTION;
            break;

            case SDL_MOUSEBUTTONDOWN:
                m_State = BUTTON_MOUSE_DOWN;
            break;

            case SDL_MOUSEBUTTONUP:
                m_State = BUTTON_MOUSE_UP;
            break;
            }
        }
    }
}

void Button::draw(Graphics &graphics)
{
    SDL_Renderer* r = graphics.getRenderer();

    switch(m_State)
    {
    case BUTTON_MOUSE_OUT:
        SDL_SetRenderDrawColor(r, 255, 0, 0, m_Alpha);
    break;
    case BUTTON_MOUSE_OVER_MOTION:
        SDL_SetRenderDrawColor(r, 0, 255, 255, m_Alpha);
    break;
    case BUTTON_MOUSE_DOWN:
        SDL_SetRenderDrawColor(r, 0, 255, 0, m_Alpha);
    break;
    case BUTTON_MOUSE_UP:
        SDL_SetRenderDrawColor(r, 0, 0, 255, m_Alpha);
    break;
    }

    SDL_RenderFillRect(r, &m_Rect);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
}

