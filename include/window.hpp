#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "global.hpp"
#include "signal_beta.hpp"

class Window{
    public:
        Window();
        ~Window();
        Result createWindow();
        void destroyWindow();
        Result createRenderer();

        SDL_Renderer* get_renderer() { return renderer; }
        bool is_running = false;



        uint32_t window_width = SCREEN_WIDTH;
        uint32_t window_height = SCREEN_HEIGHT;

    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;





};

#endif