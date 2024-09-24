#ifndef GRID_HPP
#define GRID_HPP

#include <SDL2/SDL.h>
#include "signal_beta.hpp"


class Grid
{
private:
    SDL_Texture* grid_texture = nullptr;

    int g_height = 0;
    int g_width = 0;
    int g_cell_size = 0;

    SDL_Renderer* renderer;

public:
    Grid(SDL_Renderer *render ,int height, int width, int cell_size);
    SDL_Texture* createGrid();
    ~Grid() { SDL_DestroyTexture(grid_texture);};
    

    Signal_Beta<> window_resized;
};



#endif