#include "utils/input.h"

Input::Input()
{

}

void Input::beginNewFrame()
{
    m_PressedKeys.clear();
    m_ReleasedKeys.clear();
    m_PressedButtons.clear();
    m_ReleasedButtons.clear();
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

void Input::mouseDownEvent(const SDL_Event &e)
{
    m_PressedButtons[e.button.button] = true;
    m_HeldButtons[e.button.button] = true;
}

void Input::mouseUpEvent(const SDL_Event &e)
{
    m_ReleasedButtons[e.button.button] = true;
    m_HeldButtons[e.button.button] = false;
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

bool Input::wasButtonPressed(int button)
{
    return m_PressedButtons[button];
}

bool Input::wasButtonReleased(int button)
{
    return m_ReleasedButtons[button];
}

bool Input::isButtonHeld(int button)
{
    return m_HeldButtons[button];
}

void Input::clearAll()
{
    m_PressedKeys.clear();
    m_ReleasedKeys.clear();
    m_HeldKeys.clear();

    m_PressedButtons.clear();
    m_ReleasedButtons.clear();
    m_HeldButtons.clear();
}
