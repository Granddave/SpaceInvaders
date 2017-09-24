#ifndef GLOBALS
#define GLOBALS

#include <string>

#define PRINT_FPS 0

namespace globals {
    const bool sounds = false;
}

struct Vec2{
    int x, y;
    Vec2() : x(0), y(0) {}
    Vec2(int x, int y) : x(x), y(y) {}
    static Vec2 zero() { return Vec2(); }
};

struct Vec2f{
    float x, y;
    Vec2f() : x(0.0f), y(0.0f) {}
    Vec2f(float x, float y) : x(x), y(y) {}
    static Vec2f zero() { return Vec2f(); }
};

#endif // GLOBALS
