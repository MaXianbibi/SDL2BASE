#include "../include/Grid.hpp"

#include "../include/utiles.hpp"

#include <iostream>

Grid::Grid(SDL_Renderer *render, int height, int width, int cell_size)
{
    g_height = height;
    g_width = width;
    g_cell_size = cell_size;
    renderer = render;

    grid_texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    if (grid_texture == nullptr)
    {
        std::cerr << "Failed to create grid texture: " << SDL_GetError() << std::endl;
        fatal("Failed to create grid texture");
    }
}

SDL_Texture *Grid::createGrid()
{
    SDL_SetRenderTarget(renderer, grid_texture);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < g_height; i += g_cell_size)
    {
        SDL_RenderDrawLine(renderer, 0, i, g_width, i);
    }

    for (int i = 0; i < g_width; i += g_cell_size)
    {
        SDL_RenderDrawLine(renderer, i, 0, i, g_height);
    }

    SDL_SetRenderTarget(renderer, nullptr);

    return grid_texture;
}