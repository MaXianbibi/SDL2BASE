#include "../include/Wall.hpp"
#include <iostream>
#include "../include/utiles.hpp"


void Wall::createWallTexture(SDL_Renderer *renderer, Color color)
{
    if (wall_texture != nullptr)
    {
        SDL_DestroyTexture(wall_texture);
        wall_texture = nullptr;
    }

    wall_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    if (wall_texture == nullptr)
    {
        std::cerr << "Failed to create wall texture: " << SDL_GetError() << std::endl;
        fatal("Failed to create wall texture");
    }
    SDL_SetTextureBlendMode(wall_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, wall_texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Couleur noire avec alpha 0 (transparent)
    SDL_RenderClear(renderer);

    color = {0, 0, 0xFF, 0xE0};

    if (fill)
    {
        fillPolygon(renderer, polygon, color);
    }
    border_color = {0, 0, 0xFF, 255};

    SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
    for (size_t i = 0; i < polygon.size(); i++)
    {
        int next = (i + 1) % polygon.size();
        SDL_RenderDrawLine(renderer, polygon[i].x, polygon[i].y, polygon[next].x, polygon[next].y);

        std::cout << polygon[i].x << " " << polygon[i].y << std::endl;
    }

    SDL_SetRenderTarget(renderer, nullptr);
}

Wall::Wall(Polygon polygon)
{
    if (polygon.size() < 3)
    {
        std::cerr << "A polygon must have at least 3 points" << std::endl;
        fatal("A polygon must have at least 3 points");
    }
    else {
        this->is_finished = true;
        this->is_active = true;
    }
    this->polygon = polygon;
    init();
};


void Wall::init()
{
    std::cout << "test" << std::endl;
    
    // Initialiser min_x et min_y à la première valeur du polygone
    int min_x = polygon[0].x;
    int min_y = polygon[0].y;

    // Trouver les minima du polygone (min_x et min_y)
    for (size_t i = 1; i < polygon.size(); i++) // commencer à i = 1 car on a déjà pris le premier point
    {
        if (polygon[i].x < min_x)
            min_x = polygon[i].x;
        if (polygon[i].y < min_y)
            min_y = polygon[i].y;
    }

    // Définir l'offset pour repositionner le polygone

    // Translater tous les points du polygone pour qu'ils commencent à (0, 0)
    for (size_t i = 0; i < polygon.size(); i++)
    {
        polygon[i].x -= min_x;
        polygon[i].y -= min_y;
    }

    // Calculer les dimensions maximales du polygone après translation
    int max_x = polygon[0].x;
    int max_y = polygon[0].y;
    for (size_t i = 1; i < polygon.size(); i++) // commencer à i = 1 pour éviter de re-vérifier le premier point
    {
        if (polygon[i].x > max_x)
            max_x = polygon[i].x;
        if (polygon[i].y > max_y)
            max_y = polygon[i].y;
    }

    
    setOffset({min_x, min_y});

    // Déterminer la hauteur et la largeur de la texture en fonction des nouvelles coordonnées du polygone
    height = max_y + 1;
    width = max_x + 1;
}


