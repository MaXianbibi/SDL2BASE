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


        bool is_running = false;


        Signal_Beta<> escape_signal;

        Signal_Beta<int> damage_taken_signal;

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;



};

#endif