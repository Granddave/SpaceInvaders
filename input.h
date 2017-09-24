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

    void mouseDownEvent(const SDL_Event &e);
    void mouseUpEvent(const SDL_Event& e);

    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyReleased(SDL_Scancode key);
    bool isKeyHeld(SDL_Scancode key);

    bool wasButtonPressed(int button);
    bool wasButtonReleased(int button);
    bool isButtonHeld(int button);

private:
    std::map<SDL_Scancode, bool> m_HeldKeys;
    std::map<SDL_Scancode, bool> m_PressedKeys;
    std::map<SDL_Scancode, bool> m_ReleasedKeys;

    std::map<int, bool> m_HeldButtons;
    std::map<int, bool> m_PressedButtons;
    std::map<int, bool> m_ReleasedButtons;
};

#endif // INPUT_H
