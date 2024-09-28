#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "../include/window.hpp"
#include "../include/signal_beta.hpp"
#include "../include/Grid.hpp"
#include "../include/EventManager.hpp"
#include "../include/utiles.hpp"
#include "../include/Balls.hpp"
#include "../include/Wall.hpp"
#include <vector>
#include <memory>

// Définir le framerate cible
const int FRAME_DELAY = 1000 / TARGET_FPS;

std::vector<std::shared_ptr<StaticElement>> Element::elements;

int main(int argc, char **argv)
{
    // WINDOW + GRID
    Window window;
    window.createWindow();
    window.createRenderer();
    Grid grid(window.get_renderer(), window.window_height, window.window_width, 20);
    SDL_Texture *grid_texture = grid.createGrid();

    // EVENT
    SDL_Event event;
    uint32_t frame_start = 0;
    float delta_time = 0;

    // BALL
    std::vector<std::shared_ptr<Balls>> balls;
    for (int i = 0; i < 1; i++)
    {
        auto ball = std::make_shared<Balls>();
        ball->setPosition(550 + 250 * i, 0);
        balls.push_back(ball); // Stocker le pointeur dans le vecteur
    }

    Balls::createTexture(window.get_renderer(), balls.at(0)->getRadius(), 0xFF0000FF);
    SDL_Texture *rayon_texture = Balls::createRayonTexture(window.get_renderer(), balls.at(0)->getRayonRadius(), 0xFF000080);
    Polygon square = {
        {0, 0},
        {150, 150},
        {75, 200},
        {0, 150},
    };


    // Floor
    Polygon floor = {
         {0, 0},
        {3000, 0},
        {3000, 200},
        {0, 200},
    };

    std::shared_ptr<Wall> wall = std::make_shared<Wall>(square);
    std::shared_ptr<Wall> floor_wall = std::make_shared<Wall>(floor);
    wall->setFilled(true);
    floor_wall->setFilled(true);
    wall->createWallTexture(window.get_renderer(), 0xFF0000FF);
    floor_wall->createWallTexture(window.get_renderer(), 0xFF0000FF);
    wall->setOffset({500, 200});
    floor_wall->setOffset({0, 500});

    Element::elements.push_back(wall);
    Element::elements.push_back(floor_wall);

    while (window.is_running)
    {
        // INIT PROCESS
        frame_start = SDL_GetTicks();

        // EVENT
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    EMIT_SIGNAL("close_window");
            if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                    EMIT_SIGNAL("close_window");
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                    EMIT_SIGNAL("window_resize", event.window.data1, event.window.data2);
            }
        }

        // Process
        EMIT_SIGNAL("process", delta_time);

        // RENDER
        SDL_RenderClear(window.get_renderer());
        SDL_RenderCopy(window.get_renderer(), grid_texture, NULL, NULL);

        for (size_t i = 0; i < balls.size(); i++)
        {
            SDL_Rect ball_rect = {
                static_cast<int>(balls[i]->getCenter().x),
                static_cast<int>(balls[i]->getCenter().y),
                static_cast<int>(balls[i]->getRadius() * 2),
                static_cast<int>(balls[i]->getRadius() * 2)
            };
            SDL_Rect rayon_rect = {
                static_cast<int>(balls[i]->getDetectionCenter().x),
                static_cast<int>(balls[i]->getDetectionCenter().y),
                static_cast<int>(balls[i]->getRayonRadius() * 2),
                static_cast<int>(balls[i]->getRayonRadius() * 2)
            };

            SDL_RenderCopy(window.get_renderer(), rayon_texture, NULL, &rayon_rect);
            SDL_RenderCopy(window.get_renderer(), Balls::ball_texture, NULL, &ball_rect);
        }

        // TESTING COLLISION
   

        for (auto &element : Element::elements)
        {
            auto wall = std::dynamic_pointer_cast<Wall>(element);
            if (wall)
            {
                SDL_Rect element_rect = {
                    wall->getOffset().x,
                    wall->getOffset().y,
                    wall->width,
                    wall->height,
                };

                SDL_RenderCopy(window.get_renderer(), wall->wall_texture, NULL, &element_rect);
            }
        }

        SDL_RenderPresent(window.get_renderer());

        // DELAY
        uint32_t frame_time = SDL_GetTicks() - frame_start;
        if (FRAME_DELAY > frame_time)
        {
            SDL_Delay(FRAME_DELAY - frame_time);
        }
        delta_time = frame_time / 1000.0f;
    }

    return 0;
}
