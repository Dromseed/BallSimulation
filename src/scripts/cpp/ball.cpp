#include <stdio.h>
#include <math.h>

#include "ball.hpp"

Ball::Ball(int x, int y, int Vx, int Vy, int radius) 
    : x(x), y(y), Vx(Vx), Vy(Vy), radius(radius), bonkSound("../sound/Bonk_Sound_Effect.wav") {}

void Ball::update(Ball& b, double deltaTime, double gravity)
{
    bonkSound.Volume(0.1f);
    
    if(isDragging) return;
    bool onGround = y >= WINDOW_HEIGHT - radius;

    // Ball is moving:
    b.Vy += gravity * deltaTime;
    b.y += b.Vy * deltaTime;
    b.x += b.Vx * deltaTime;

    // Conditions to not going outside of the window:
    // down:
    if(b.y > WINDOW_HEIGHT - b.radius)
    {
        b.y = WINDOW_HEIGHT - radius;
        if(!b.wasTouchingGround && std::abs(b.Vy) > 20.0)
        {
            b.bonkSound.Play();
        }
        b.wasTouchingGround = true;
        b.Vy = -b.Vy * bounceDumping;
    }
    else
    {
        b.wasTouchingGround = false;
    }
    // up:
    if(b.y < b.radius)
    {
        b.y = radius;
        if(!b.wasTouchingGround && std::abs(b.Vy) > 20.0)
        {
            b.bonkSound.Play();
        }
        b.wasTouchingGround = true;
        b.Vy = -b.Vy * bounceDumping;
    }
    else
    {
        b.wasTouchingGround = false;
    }
    // right:
    if(b.x > WINDOW_WIDTH - b.radius)
    {
        b.x = WINDOW_WIDTH - radius;
        if(!b.wasTouchingGround && std::abs(b.Vy) > 20.0)
        {
            b.bonkSound.Play();
        }
        b.wasTouchingGround = true;
        b.Vx = -b.Vx * bounceDumping;
    }
    else
    {
        b.wasTouchingGround = false;
    }
    // left:
    if(b.x < b.radius)
    {
        b.x = radius;
        if(!b.wasTouchingGround && std::abs(b.Vy) > 20.0)
        {
            b.bonkSound.Play();
        }
        b.wasTouchingGround = true;
        b.Vx = -b.Vx * bounceDumping;
    }
    else
    {
        b.wasTouchingGround = false;        
    }
    if(onGround)
    {
        const double friction = 0.990;
        b.Vx *= friction;
        if(std::abs(b.Vx) < 0.5)
        {
            b.Vx = 0;
        }
    }
        

    //Logging ball position: (not necessary, for debugging).
    //printf("Ball.Vx: %d\n", (int)b.Vx);
}