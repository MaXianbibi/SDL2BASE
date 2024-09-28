#ifndef WALL_HPP
#define WALL_HPP

#include "Element.hpp"

#include <SDL2/SDL.h>

class Wall : public StaticElement
{
private:
    Wall() {};
    Vector2<int> offset = {0, 0};

public:
    Wall(Polygon polygon);
    virtual ~Wall()
    {
        if (wall_texture != nullptr)
            SDL_DestroyTexture(wall_texture);
    }

    void setFilled(bool fill) { this->fill = fill; }
    void createWallTexture(SDL_Renderer *renderer, Color color);

    SDL_Texture *wall_texture = nullptr;
    void setOffset(Vector2<int> offset)
    {
        this->offset = offset;
        for (auto &point : polygon)
        {
            point.x += offset.x;
            point.y += offset.y;
        }
    }
    Vector2<int> getOffset() { return offset; }

    int height = 0;
    int width = 0;
};

#endif