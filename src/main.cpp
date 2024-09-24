#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "../include/window.hpp"
#include "../include/signal_beta.hpp"

#include "../include/Grid.hpp"

#include "../include/EventManager.hpp"

// Définir le framerate cible
const int FRAME_DELAY = 1000 / TARGET_FPS;

int main(int argc, char **argv)
{
    Window window;
    window.createWindow();
    window.createRenderer();
    Grid grid(window.get_renderer(), window.window_height, window.window_width, 20);
    SDL_Texture *grid_texture = grid.createGrid();





    ADD_SIGNAL("damage_taken", int)->connect([](int damage) {std::cout << "Damage taken: " << damage << std::endl;});



    SDL_Event event;
    uint32_t frame_start = 0;
    float delta_time = 0;
    while (window.is_running)
    {
        // INIT PROCESS
        frame_start = SDL_GetTicks();

        // EVENT
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    // escape_signal->emit();
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                {
                    EMIT_SIGNAL("damage_taken", 10);
                }
            }

            if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    // event_manager.window_resized.emit();
                    window.window_width = event.window.data1;  // Nouvelle largeur
                    window.window_height = event.window.data2; // Nouvelle hauteur

                    // Ajustements que tu veux faire en fonction de la nouvelle taille
                    std::cout << "Fenêtre redimensionnée : "
                              << window.window_width << "x" << window.window_height << std::endl;

                    // Si tu utilises un renderer, tu peux aussi adapter le viewport :
                    SDL_RenderSetViewport(window.get_renderer(), NULL); // Adapter le viewport à la nouvelle taille
                }
            }
        }

        // RENDER
        SDL_RenderClear(window.get_renderer());
        SDL_RenderCopy(window.get_renderer(), grid_texture, NULL, NULL);
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
