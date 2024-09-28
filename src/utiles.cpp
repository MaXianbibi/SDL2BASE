#include <SDL2/SDL.h>
#include "../include/utiles.hpp"
#include <string>
#include <iostream>
#include "../include/global.hpp"

#include <cmath>
#include <algorithm>


#include "../include/Element.hpp"

void fatal(std::string message){
    std::cerr << message << std::endl;
    exit(-1);
}

void drawPixel(SDL_Renderer* renderer, int x, int y)
{
    SDL_RenderDrawPoint(renderer, x, y);
}


void drawFilledCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, Color color)
{
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    while (x >= y)
    {
        // Pour chaque ligne du cercle, dessiner une ligne horizontale pour remplir l'intérieur
        SDL_RenderDrawLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y);
        SDL_RenderDrawLine(renderer, centerX - x, centerY - y, centerX + x, centerY - y);
        SDL_RenderDrawLine(renderer, centerX - y, centerY + x, centerX + y, centerY + x);
        SDL_RenderDrawLine(renderer, centerX - y, centerY - x, centerX + y, centerY - x);

        y++;
        if (radiusError < 0)
        {
            radiusError += 2 * y + 1;
        }
        else
        {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}

void fillPolygon(SDL_Renderer* renderer, const Polygon& polygon, Color color) {
    // Set the draw color to the fill color
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Find the minimum and maximum y-coordinates of the polygon
    int min_y = polygon[0].y;
    int max_y = polygon[0].y;
    for (const auto& point : polygon) {
        if (point.y < min_y) min_y = point.y;
        if (point.y > max_y) max_y = point.y;
    }

    // Iterate over each scanline (horizontal line) between min_y and max_y
    for (int y = min_y; y <= max_y; y++) {
        std::vector<int> nodeX;  // List to store x-coordinates of intersections

        // Find the intersections of the scanline with the edges of the polygon
        for (size_t i = 0; i < polygon.size(); i++) {
            int next = (i + 1) % polygon.size();
            int x1 = polygon[i].x;
            int y1 = polygon[i].y;
            int x2 = polygon[next].x;
            int y2 = polygon[next].y;

            // Check if the scanline intersects the edge (y1, y2)
            if ((y1 < y && y2 >= y) || (y2 < y && y1 >= y)) {
                int x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                nodeX.push_back(x);
            }
        }

        // Sort the intersections
        std::sort(nodeX.begin(), nodeX.end());

        // Draw lines between pairs of intersections
        for (size_t i = 0; i < nodeX.size(); i += 2) {
            if (i + 1 < nodeX.size()) {
                SDL_RenderDrawLine(renderer, nodeX[i], y, nodeX[i + 1], y);
            }
        }
    }
}


// Check if a point is inside a polygon
// Je comprends R a cette algo
bool isPointInPolygon(int x, int y, const Polygon& polygon) {
    bool inside = false;
    int n = polygon.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        int xi = polygon[i].x, yi = polygon[i].y;
        int xj = polygon[j].x, yj = polygon[j].y;
        bool intersect = ((yi > y) != (yj > y)) && 
                         (x < (xj - xi) * (y - yi) / (yj - yi) + xi);
        if (intersect) {
            inside = !inside;
        }
    }
    return inside;
}


// Je comprnend R
// Ray-casting algorithm
SDL_Point closestPointOnSegment(int x1, int y1, int x2, int y2, int px, int py) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    if (dx == 0 && dy == 0) {
        return {x1, y1};
    }
    float t = ((px - x1) * dx + (py - y1) * dy) / (dx * dx + dy * dy);
    t = std::max(0.0f, std::min(1.0f, t));  

    SDL_Point closestPoint = {
        static_cast<int>(x1 + t * dx),
        static_cast<int>(y1 + t * dy)
    };
    return closestPoint;
}

bool isPointInBoundingBox(int px, int py, const Polygon& polygon) {
    int min_x = polygon[0].x, min_y = polygon[0].y;
    int max_x = polygon[0].x, max_y = polygon[0].y;

    for (const auto& point : polygon) {
        if (point.x < min_x) min_x = point.x;
        if (point.x > max_x) max_x = point.x;
        if (point.y < min_y) min_y = point.y;
        if (point.y > max_y) max_y = point.y;
    }

    // Vérifier si le point est dans la bounding box
    return (px >= min_x && px <= max_x && py >= min_y && py <= max_y);
}

SDL_Point closestPointOnPolygon(int px, int py, const Polygon& polygon, int *_distance) {
    SDL_Point closestPoint = {static_cast<int>(polygon[0].x), static_cast<int>(polygon[0].y)};
    float closestDistance = std::numeric_limits<float>::max();

    for (size_t i = 0; i < polygon.size(); i++) {
        int next = (i + 1) % polygon.size();
        SDL_Point currentClosest = closestPointOnSegment(
            polygon[i].x, polygon[i].y,
            polygon[next].x, polygon[next].y,
            px, py
        );
        float dx = currentClosest.x - px;
        float dy = currentClosest.y - py;
        float distance = dx * dx + dy * dy;  
        if (distance < closestDistance) {
            closestDistance = distance;
            closestPoint = currentClosest;   
        }
    }
    *_distance = (int)std::sqrt(closestDistance);
    return closestPoint;
}


Vector2<float> calculateNormal(SDL_Point p1, SDL_Point p2) {
    // Calcul du vecteur du segment
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    
    // La normale perpendiculaire : (-dy, dx) ou (dy, -dx)
    return {-dy, dx};  // Normale perpendiculaire
}


Vector2<float> normalize(Vector2<float> vec) {
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length != 0) {
        vec.x /= length;
        vec.y /= length;
    }
    return vec;
}

Vector2<float> reflect(Vector2<float> velocity, Vector2<float> normal) {
    // Produit scalaire entre la vitesse et la normale
    float dotProduct = velocity.x * normal.x + velocity.y * normal.y;

    // Calcul de la réflexion : V' = V - 2 * (V • N) * N
    return {
        velocity.x - 2 * dotProduct * normal.x,
        velocity.y - 2 * dotProduct * normal.y
    };
}


