#include <SDL2/SDL.h>
#include "../include/window.hpp"
#include "../include/utiles.hpp"


Window::Window()
{
    window = NULL;
    renderer = NULL;
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

    window = SDL_CreateWindow("Baller", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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