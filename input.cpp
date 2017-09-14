#include "input.h"

Input::Input()
{

}

void Input::beginNewFrame()
{
    m_PressedKeys.clear();
    m_ReleasedKeys.clear();
}

void Input::keyDownEvent(const SDL_Event &e)
{
    m_PressedKeys[e.key.keysym.scancode] = true;
    m_HeldKeys[e.key.keysym.scancode] = true;
}

void Input::keyUpEvent(const SDL_Event &e)
{
    m_ReleasedKeys[e.key.keysym.scancode] = true;
    m_HeldKeys[e.key.keysym.scancode] = false;
}

bool Input::wasKeyPressed(SDL_Scancode key)
{
    return m_PressedKeys[key];
}

bool Input::wasKeyReleased(SDL_Scancode key)
{
    return m_ReleasedKeys[key];
}

bool Input::isKeyHeld(SDL_Scancode key)
{
    return m_HeldKeys[key];
}

void Input::clearAll()
{
    m_PressedKeys.clear();
    m_ReleasedKeys.clear();
    m_HeldKeys.clear();
}
