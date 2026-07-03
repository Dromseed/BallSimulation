#pragma once

#include "ball.hpp"

#include <SDL3/SDL.h>

struct Renderer
{
    void drawBackground(SDL_Renderer* r);
    void drawBall(SDL_Renderer* r, const Ball& b);
};