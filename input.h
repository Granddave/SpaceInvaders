#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <map>

class Input
{
public:
    Input();

    void beginNewFrame();
    void clearAll();
    void keyDownEvent(const SDL_Event& e);
    void keyUpEvent(const SDL_Event& e);

    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyReleased(SDL_Scancode key);
    bool isKeyHeld(SDL_Scancode key);

private:
    std::map<SDL_Scancode, bool> m_HeldKeys;
    std::map<SDL_Scancode, bool> m_PressedKeys;
    std::map<SDL_Scancode, bool> m_ReleasedKeys;
};

#endif // INPUT_H
