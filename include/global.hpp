#ifndef GLOBAL_HPP
#define GLOBAL_HPP


#include <cstdint>

enum Result
{
    SUCCESS,
    FAILURE
};

template <typename T>
struct Vector2
{
    T x;
    T y;
};

template <typename T>
struct Rect
{
    T x;
    T y;
    T w;
    T h;
};

union Color
{
    struct
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
    uint32_t value;

    // Constructeur qui initialise par `value`
    Color(uint32_t v) : value(v) {}
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}
};




#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TARGET_FPS 60

#endif