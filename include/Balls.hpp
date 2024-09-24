#ifndef BALL_HPP
#define BALL_HPP


#include "global.hpp"

class Balls
{
private:
    float radius = 10.0f;
    Color color = 0xFF0000;
    Vector2<int> position = {0, 0};
    
public:
    Balls(int radius, int color) : radius(radius), color(color) {};
    Balls() {};
    ~Balls() {};

    void setPosition(int x, int y) {position.x = x;position.y = y;}
    Vector2<int> getPosition() {return position;}

    float getRadius() {return radius;}
    Color getColor() {return color;}
    
};


#endif