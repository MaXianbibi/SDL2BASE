#ifndef UTILES_HPP
#define UTILES_HPP

#include <string>
#include "global.hpp"

void fatal(std::string message);

void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, Color color);
void drawPixel(SDL_Renderer* renderer, int x, int y);


#endif