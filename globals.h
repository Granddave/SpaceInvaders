#ifndef GLOBALS
#define GLOBALS

#include <string>

#define FULLSCREEN 0

namespace globals
{
#if FULLSCREEN
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;
#else
    const int SCREEN_WIDTH = 720;
    const int SCREEN_HEIGHT = 540;
#endif
    const int PIXEL_SCALE = 2;
    const int FPS = 60;
    const int MAX_FRAME_TIME = 1000 / FPS;

    const std::string WINDOW_TITLE = "Space Invaders";
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
