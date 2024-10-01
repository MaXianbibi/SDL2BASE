#ifndef GLOBAL_HPP
#define GLOBAL_HPP


#include <cstdint>
#include <iostream>
#include <cmath>

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

    Vector2<T> operator+(const Vector2<T> &v)
    {
        return {x + v.x, y + v.y};
    }

    Vector2<T> operator-(const Vector2<T> &v)
    {
        return {x - v.x, y - v.y};
    }

    Vector2<T> operator*(const T &s)
    {
        return {x * s, y * s};
    }

    Vector2<T> operator/(const T &s)
    {
        return {x / s, y / s};
    }

    Vector2<T> &operator+=(const Vector2<T> &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2<T> &operator-=(const Vector2<T> &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector2<T> &operator*=(const T &s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    Vector2<T> &operator/=(const T &s)
    {
        x /= s;
        y /= s;
        return *this;
    }

    bool operator==(const Vector2<T> &v)
    {
        return x == v.x && y == v.y;
    }

    bool operator!=(const Vector2<T> &v)
    {
        return x != v.x || y != v.y;
    }

    Vector2<T> &operator-()
    {
        x = -x;
        y = -y;
        return *this;
    }

    Vector2<T> operator*(const Vector2<T> &v)
    {
        return {x * v.x, y * v.y};
    }

    Vector2<T> &operator*=(const Vector2<T> &v)
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    // operator <<
    friend std::ostream &operator<<(std::ostream &os, const Vector2<T> &v)
    {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }


    float distance_to(const Vector2<T> &v)
    {
        return sqrt((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y));
    }

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