#ifndef UTILES_HPP
#define UTILES_HPP

#include <string>
#include "global.hpp"

#include "Element.hpp"
#include <cmath>


void fatal(std::string message);

void drawFilledCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, Color color);
void drawPixel(SDL_Renderer* renderer, int x, int y);
void fillPolygon(SDL_Renderer* renderer, const Polygon& polygon, Color color);
bool isPointInPolygon(int x, int y, const Polygon& polygon);
SDL_Point closestPointOnSegment(int x1, int y1, int x2, int y2, int px, int py);
SDL_Point closestPointOnPolygon(int px, int py, const Polygon& polygon, int *_distance);

Vector2<float> calculateNormal(SDL_Point p1, SDL_Point p2);
Vector2<float> normalize(Vector2<float> vec);
Vector2<float> reflect(Vector2<float> velocity, Vector2<float> normal);


template<typename T>
float magnitude(const Vector2<T>& vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

#endif