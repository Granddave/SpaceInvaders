#ifndef UTILS_H
#define UTILS_H

#include "gmath/Vector2.hpp"
#include <SDL2/SDL_rect.h>

#define NOT_USED(x) ((void)(x))

bool pointInsideRect(const Vector2& p, const SDL_Rect &r);

#endif // UTILS_H
