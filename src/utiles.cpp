#include <SDL2/SDL.h>
#include "../include/utiles.hpp"
#include <string>
#include <iostream>
#include "../include/global.hpp"

#include <cmath>



void fatal(std::string message){
    std::cerr << message << std::endl;
    exit(-1);
}

void drawPixel(SDL_Renderer* renderer, int x, int y)
{
    SDL_RenderDrawPoint(renderer, x, y);
}


void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, Color color)
{
    int x, y;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (x = -radius; x <= radius; x++)
    {
        y = static_cast<int>(sqrt(radius * radius - x * x)); // Calcul de y à partir de l'équation du cercle

        drawPixel(renderer, centerX + x, centerY + y);
        drawPixel(renderer, centerX + x, centerY - y);
    }
}
