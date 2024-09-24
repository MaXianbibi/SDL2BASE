#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "../include/window.hpp"
#include "../include/signal_beta.hpp"

// Définir le framerate cible
const int FRAME_DELAY = 1000 / TARGET_FPS;

void damage_taken(int damage)
{
    std::cout << "Damage taken: " << damage << std::endl;
}

int main(int argc, char **argv)
{
    Window window;

    // Connexion des signaux
    window.damage_taken_signal.connect(damage_taken);
    window.escape_signal.connect([&window]() {
        window.is_running = false;
    });

    window.createWindow();

    SDL_Event event;
    uint32_t frame_start = 0;
    float delta_time = 0;

    while (window.is_running)
    {
        frame_start = SDL_GetTicks(); // Temps de début de la frame

        // Gestion des événements avec une boucle while pour capturer tous les événements
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    window.escape_signal.emit();
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                {
                    window.damage_taken_signal.emit(10);
                }
            }
        }

        // Ici, tu peux ajouter du code de rendu (si tu en as besoin)

        // Calcul du temps écoulé pour la frame
        uint32_t frame_time = SDL_GetTicks() - frame_start;

        // Limitation du framerate
        if (FRAME_DELAY > frame_time)
        {
            SDL_Delay(FRAME_DELAY - frame_time);
        }

        // Calcul du delta_time (en secondes)
        delta_time = frame_time / 1000.0f;

        std::cout << "Delta time: " << delta_time << std::endl;
    }

    return 0;
}
