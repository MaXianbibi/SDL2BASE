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
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) EMIT_SIGNAL("escape_key_pressed");
   
            }

            if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    EMIT_SIGNAL("escape_key_pressed");
                }
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {

                    std::cout << window.window_width << " " << window.window_height << std::endl;
                    EMIT_SIGNAL("window_resize", event.window.data1, event.window.data2);
                    
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
