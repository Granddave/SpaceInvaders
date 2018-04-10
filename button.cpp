#include "button.h"
#include "globals.h"

#include <iostream>
Button::Button(const std::string text, int x, int y, int w, int h)
    : m_Text(text),
      m_Rect({x, y, w, h}),
      m_Alpha(10),
      m_State(BUTTON_MOUSE_OUT)
{

}

void Button::setText(const std::string text)
{
    m_Text = text;
}

int Button::state()
{
    return m_State;
}

void Button::handleEvents(SDL_Event& e)
{
    if(e.type == SDL_MOUSEMOTION ||
       e.type == SDL_MOUSEBUTTONDOWN ||
       e.type == SDL_MOUSEBUTTONUP)
    {
        Vec2 p;
        SDL_GetMouseState(&p.x, &p.y);

        if(p.isInside(m_Rect) == false)
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

void Button::draw(Graphics *graphics)
{
    SDL_Renderer* r = graphics->getRenderer();

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

    // Todo: Render text

    SDL_RenderFillRect(r, &m_Rect);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
}
