#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SDL.h>
#include "gamestate.h"
#include "graphics.h"
#include "input.h"
#include "button.h"

class MenuState : public GameState
{
public:
    void init(Graphics* graphics);
    void clean();

    void pause();
    void resume();

    void handleEvents(Game* game);
    void update(Game* game, int ms);
    void draw(Graphics& graphics);

    static MenuState* instance()
    {
        return &m_MenuState;
    }

protected:
    MenuState() {}

private:
    static MenuState m_MenuState;
    Input m_Input;

    Button* m_Button;

};

#endif // MENUSTATE_H
