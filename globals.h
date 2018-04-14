#ifndef GLOBALS
#define GLOBALS

#include <string>
#include <SDL2/SDL_rect.h>

#define PRINT_FPS 0

namespace globals {
    const bool sounds = false;
}

struct Vec2{
    int x, y;
    Vec2() : x(0), y(0) {}
    Vec2(int x, int y) : x(x), y(y) {}
    static Vec2 zero() { return Vec2(); }
    bool isInside(const SDL_Rect &r)
    {
        return ((this->x >= r.x) && (this->x < (r.x + r.w)) &&
                (this->y >= r.y) && (this->y < (r.y + r.h)) ) ? true : false;
    }

    Vec2 operator+ (const Vec2& other) const
    {
        return Vec2(x + other.x, y + other.y);
    }
};

struct Vec2f{
    float x, y;
    Vec2f() : x(0.0f), y(0.0f) {}
    Vec2f(float x, float y) : x(x), y(y) {}
    static Vec2f zero() { return Vec2f(); }
    bool isInside(const SDL_Rect &r)
    {
        return ((this->x >= r.x) && (this->x < (r.x + r.w)) &&
                (this->y >= r.y) && (this->y < (r.y + r.h)) ) ? true : false;
    }
    void normalize()
    {
        float dirLen = sqrt(this->x * this->x + this->y * this->y);
        this->x = this->x / dirLen;
        this->y = this->y / dirLen;
    }

    Vec2f operator+ (const Vec2f& other) const
    {
        return Vec2f(x + other.x, y + other.y);
    }
};

#endif // GLOBALS
