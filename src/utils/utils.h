#ifndef UTILS_H
#define UTILS_H

#include "gmath/Vector2.hpp"

#include <SDL2/SDL_rect.h>
#include <Box2D/Box2D.h>
#define NOT_USED(x) ((void)(x))

bool pointInsideRect(const Vector2& p, const SDL_Rect &r);

b2Vec2 worldToPixel(b2Vec2 world);
b2Vec2 pixelToWorld(b2Vec2 pixel);

#endif // UTILS_H
