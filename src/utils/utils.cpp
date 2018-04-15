#include "utils/utils.h"

bool pointInsideRect(const Vector2& p, const SDL_Rect &r)
{
    return ((p.X >= r.x) && (p.X < (r.x + r.w)) &&
            (p.Y >= r.y) && (p.Y < (r.y + r.h)) ) ? true : false;
}
