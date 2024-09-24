#include <SDL2/SDL.h>
#include "../include/window.hpp"
#include "../include/utiles.hpp"
#include "../include/EventManager.hpp"


Window::Window()
{
    window = NULL;
    renderer = NULL;


    ADD_SIGNAL("escape_key_pressed")->connect([this]() {this->is_running = false;});


    std::cout << "hmm" << std::endl;

    ADD_SIGNAL("window_resize", int, int)->connect([this](int w, int h) {

        window_width = w;
        window_height = h;

        std::cout << "windows update" << std::endl;
    });
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Result Window::createWindow()
{
    if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1))
    {
        std::string message = "Error initializing SDL: " + std::string(SDL_GetError());

        fatal(message);
    }

    window = SDL_CreateWindow("Baller", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        std::string message = "Error creating window: " + std::string(SDL_GetError());
        fatal(message);
    }

    is_running = true;
    return Result::SUCCESS;
}

void Window::destroyWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Result Window::createRenderer()
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::string message = "Error creating renderer: " + std::string(SDL_GetError());
        fatal(message);
    }

    return Result::SUCCESS;
}