#pragma once

#include <SDL3/SDL.h>

#include "ball.hpp"
#include "renderer.hpp"

class App
{
public:
    App();
    ~App();
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Renderer drawer;
    
    Ball ball;

    bool running;

    // Deltatime and frame realisation:
    Uint64 currentTime, lastTime = SDL_GetPerformanceCounter();
    double deltaTime = (double)(currentTime - lastTime) / SDL_GetPerformanceFrequency();
    double frameTimer;
    int frames;

    // Frame test:
    Uint64 frameStart = SDL_GetPerformanceCounter(); 
    Uint64 frameEnd = SDL_GetPerformanceCounter();
    double frameMs = (frameEnd - frameStart) * 1000.0 / SDL_GetPerformanceFrequency();

    // Getting monitor hz:
    SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
    const SDL_DisplayMode* hzMonitor = SDL_GetCurrentDisplayMode(displayID);

    // Global gravity system:
    double Gravity = 900;
};