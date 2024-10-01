#include "../include/Balls.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include "../include/utiles.hpp"
SDL_Texture *Balls::ball_texture = nullptr;

#include "../include/Element.hpp"
#include <cmath>

SDL_Texture *Balls::createTexture(SDL_Renderer *renderer, uint16_t radius, Color color)
{

    if (ball_texture != nullptr)
    {
        SDL_DestroyTexture(ball_texture);
        ball_texture = nullptr;
    }

    ball_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, radius * 2, radius * 2);
    if (ball_texture == nullptr)
    {
        std::cerr << "Failed to create grid texture: " << SDL_GetError() << std::endl;
        fatal("Failed to create grid texture");
    }

    SDL_SetTextureBlendMode(ball_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, ball_texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Couleur noire avec alpha 0 (transparent)
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    drawFilledCircle(renderer, radius, radius, radius, color);
    SDL_SetRenderTarget(renderer, nullptr);

    return ball_texture;
}

SDL_Texture *Balls::createRayonTexture(SDL_Renderer *renderer, uint16_t radius, Color color)
{
    SDL_Texture *rayon_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, radius * 2, radius * 2);
    if (rayon_texture == nullptr)
    {
        std::cerr << "Failed to create grid texture: " << SDL_GetError() << std::endl;
        fatal("Failed to create grid texture");
    }

    SDL_SetTextureBlendMode(rayon_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, rayon_texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Couleur noire avec alpha 0 (transparent)
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    drawFilledCircle(renderer, radius, radius, radius, color);
    SDL_SetRenderTarget(renderer, nullptr);

    return rayon_texture;
}

Balls::Balls()
{
    this->origin = {radius, radius};

    ADD_SIGNAL("process", float)->connect([this](float delta_time)
                                          { this->physicsUpdate(delta_time); });

    ADD_SIGNAL("start_process")->connect([this]()
                                         { this->physics = true; });
}

Vector2<float> Balls::getCenter()
{
    return position - origin;
}

void Balls::physicsUpdate(float delta_time)
{
    if (!physics)
        return;
    // Parcours des éléments pour détecter la collision avec chaque élément statique
    for (const auto &element : Element::elements)
    {
        if (!element->is_active && !element->is_finished)
        {
            continue;
        }
        int distance = 0;
        SDL_Point closestPoint = closestPointOnPolygon(this->getPosition().x, this->getPosition().y, element->getOffsetPolygon(), &distance);

        // Si la balle est en collision avec l'élément
        if (distance <= this->getRadius() && this->acceleration.y > 0)
        {
            // Corrige la pénétration dans l'élément en ajustant la position de la balle
            float penetration = this->getRadius() - distance;
            this->translate({0, -penetration});

            // Calculer le vecteur de collision
            Vector2<float> collisionVector = {
                closestPoint.x - this->getPosition().x,
                closestPoint.y - this->getPosition().y};

            // Normaliser le vecteur de collision pour obtenir la normale
            Vector2<float> normal = normalize(collisionVector);

            // Calculer le produit scalaire entre la vélocité et la normale
            float dotProduct = this->velocity.x * normal.x + this->velocity.y * normal.y;

            // Réfléchir la vélocité par rapport à la normale
            this->acceleration.x -= 2 * dotProduct * normal.x;
            this->acceleration.y -= 2 * dotProduct * normal.y;

            // Appliquer le facteur de restitution pour simuler la perte d'énergie
            this->acceleration *= 0.6f;

            // Si la vélocité devient trop faible après le rebond, la stopper
            if (this->acceleration.y > -0.2f)
            {
                this->acceleration.y = 0;
            }

            // Appliquer la restitution et limiter la vitesse après le rebond
        }
        else if (distance > this->getRadius()) // Si la balle est en chute libre
        {
            // Appliquer la gravité
            this->acceleration.y += GRAVITY * this->mass;
        }
    }

    // Limiter la vitesse maximale pour éviter des accélérations excessives
    if (this->acceleration.y > 10.0f)
    {
        this->acceleration.y = 10.0f;
    }

    // Mettre à jour la vélocité en fonction de l'accélération
    this->velocity = this->acceleration;

    // Appliquer la nouvelle position en fonction de la vélocité
    this->translate(this->velocity);
}
