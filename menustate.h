#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "gamestate.h"
#include "graphics.h"
#include "input.h"
#include "button.h"

#include <SDL2/SDL.h>
#include <vector>

class MenuState : public GameState
{
public:
    void init(Graphics* graphics);
    void clean();

    void pause();
    void resume();

    void handleEvents(Game* game);
    void update(Game* game, int ms);
    void draw();

    static MenuState* instance()
    {
        return &m_MenuState;
    }

protected:
    MenuState() { m_Graphics = NULL; }

private:
    void initButtons();

    static MenuState m_MenuState;
    Input m_Input;

    std::vector<Button*> m_Buttons;
};

#endif // MENUSTATE_H
