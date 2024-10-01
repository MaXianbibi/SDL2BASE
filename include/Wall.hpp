#ifndef WALL_HPP
#define WALL_HPP

#include "Element.hpp"

#include <SDL2/SDL.h>

class Wall : public StaticElement
{
private:
    Vector2<int> offset = {0, 0};

public:
    Wall(Polygon polygon);
    Wall() {
        this->is_finished = false;
        this->is_active = false;
    };
    virtual ~Wall()
    {
        if (wall_texture != nullptr)
            SDL_DestroyTexture(wall_texture);
    }

    void setFilled(bool fill) { this->fill = fill; }
    void createWallTexture(SDL_Renderer *renderer, Color color);

    SDL_Texture *wall_texture = nullptr;
    void init();
    Vector2<float> getPoistion() {  return position; }

    void setOffset(Vector2<int> offset) override {
        std::cout << "inited !" << std::endl;
        this->offset = offset;
        offset_ploygon = polygon;
        for (auto &point : offset_ploygon)
        {
            point.x += static_cast<float>(offset.x);
            point.y += static_cast<float>(offset.y);
        }
    }
    Vector2<int> getOffset() override { return offset; }
    int height = 0;
    int width = 0;
};

#endif