#ifndef BALL_HPP
#define BALL_HPP


#include "global.hpp"
#include <SDL2/SDL.h>
#include "EventManager.hpp"

#include "Element.hpp"

#define GRAVITY 0.0981f

class Balls : public DynamicElement
{
private:
    float radius = 20.0f;  
public:
    Balls(int radius, int color) {
        this->radius = radius;
        this->color = color;
        this->origin = {(float)radius, (float)radius};
    };

    Balls() ;
    ~Balls() { if (ball_texture != nullptr) SDL_DestroyTexture(ball_texture); };

    void setPosition(int x, int y) {
        position.x = x;position.y = y;
    }
    Vector2<float> getPosition() {return position;}

    Vector2<int> getPositionInt() {
        return Vector2<int>{(int)position.x, (int)position.y};
    }


    void translate(int x, int y) {
        position.x += x;
        position.y += y;
    }


    void translate(Vector2<float> v) {
        position += v;
    }

    void update(float dt) {
        position.y += 1;
    }


    Vector2<float> getCenter();
    Vector2<float> getOrigin() {return origin;}
    Vector2<float> getDetectionCenter() {return position - Vector2<float>{detection_radius, detection_radius};}
    
    
    static SDL_Texture *ball_texture;
    static SDL_Texture *createTexture(SDL_Renderer *renderer, uint16_t radius, Color color);
    static SDL_Texture *createRayonTexture(SDL_Renderer *renderer, uint16_t radius, Color color);
    

    float getRadius() {return radius;}
    Color getColor() {return color;}
    float getRayonRadius() {return detection_radius;}

    void physicsUpdate(float delta_time);
    
    
};


#endif