#pragma once
#include <SDL3/SDL.h>

#include "window_settings.hpp"
#include "sound.hpp"

class Ball
{
public:
    float radius;
    double x, y;
    double Vx, Vy;
    
    const double bounceDumping = 0.5;
    
    double dragVx, dragVy = 0;
    double prevMouseX, prevMouseY = 0;
    
    float offset_x = 0.0f;
    float offset_y = 0.0f;
    
    bool isDragging = false;
    bool wasTouchingGround = false;

    AudioSound bonkSound;

    Ball(int x, int y, int Vx, int Vy, int radius);
    void update(Ball& b, double deltaTime, double gravity);
};