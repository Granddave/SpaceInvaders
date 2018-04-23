#include "utils/utils.h"
#include "graphics/graphics.h"

bool pointInsideRect(const Vector2& p, const SDL_Rect &r)
{
    return ((p.X >= r.x) && (p.X < (r.x + r.w)) &&
            (p.Y >= r.y) && (p.Y < (r.y + r.h)) ) ? true : false;
}


#define WORLD_SCALE 16

b2Vec2 worldToPixel(b2Vec2 world)
{
    b2Vec2 pixel;
    pixel.x = world.x * Graphics::s_ScreenWidth / 16;
    pixel.y = Graphics::s_ScreenHeight - world.y * Graphics::s_ScreenHeight / 9;
    return pixel;
}

b2Vec2 pixelToWorld(b2Vec2 pixel)
{
    b2Vec2 world;
    world.x = pixel.x * 16 / Graphics::s_ScreenWidth;
    world.y = (Graphics::s_ScreenHeight - pixel.y) * 9  / Graphics::s_ScreenHeight;
    return world;
}
