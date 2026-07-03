#include <stdio.h>
#include <string>

#include "app.hpp"
#include "window_settings.hpp"

App::App()
    // Initialize ball (positions: x,y; speed: Vx,Vy; radius):
    : ball((WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2), 250, 1, 30)
{   
    SDL_Init(SDL_INIT_VIDEO);
    // Window:
    window = SDL_CreateWindow(nullptr, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    // Render:
    renderer = SDL_CreateRenderer(window, nullptr);
    // Vsync (I DO NOT RECOMMEND TO TURN THIS OFF! IT'S USELESS.):
    SDL_SetRenderVSync(renderer, 1);

    running = true;
}

App::~App()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

// Main loop:
void App::run()
{
    SDL_Event event;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                // ---------- Conditions to move a ball with mouse ----------
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    if(event.button.button == SDL_BUTTON_LEFT)
                    {
                        double dx = event.button.x - ball.x;
                        double dy = event.button.y - ball.y;
                        if(dx*dx + dy*dy <= ball.radius * ball.radius)
                           {
                               ball.isDragging = true;
                               
                               ball.prevMouseX = event.button.x;
                               ball.prevMouseY = event.button.y;
                               ball.Vx = 0;
                               ball.Vy = 0;
                               printf("Ball is grabbed.\n");
                           }
                    }
                    break;
                case SDL_EVENT_MOUSE_MOTION:
                    if(ball.isDragging)
                    {
                        float mouseX, mouseY;
                        SDL_GetMouseState(&mouseX, &mouseY);

                        double instVx = (mouseX - ball.prevMouseX) / deltaTime;
                        double instVy = (mouseY - ball.prevMouseY) / deltaTime;

                        const double smoothing = 0.001;
                        ball.Vx = ball.Vx * (1.0 - smoothing) + instVx * deltaTime;
                        ball.Vy = ball.Vy * (1.0 - smoothing) + instVy * deltaTime;

                        ball.x = mouseX - ball.offset_x;
                        ball.y = mouseY - ball.offset_y;

                        ball.prevMouseX = mouseX;
                        ball.prevMouseY = mouseY;
                    }
                    break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    if(event.button.button == SDL_BUTTON_LEFT)
                    {
                        ball.isDragging = false;
                        printf("Ball is thrown.\n");
                    }
                    break;
                // --------------------------------------------------------    
                // Respawning the ball:
                case SDL_EVENT_KEY_DOWN:
                    if(event.key.scancode == SDL_SCANCODE_R)
                    {
                        ball.x = WINDOW_WIDTH / 2;
                        ball.y = WINDOW_HEIGHT / 2;
                        ball.Vx = 0; 
                        ball.Vy = 0;
                    }
                // Movement with keyboard (idk why, but is exists): 
                    if(event.key.scancode == SDL_SCANCODE_D)
                    {
                        ball.Vx += 45;
                    }
                    else if (event.key.scancode == SDL_SCANCODE_A)
                    {
                        ball.Vx -= 45;
                    }
                    
                    break;
                // Quit from app:
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
            }
        }
        
        // deltaTime realisation:
        currentTime = SDL_GetPerformanceCounter();
        deltaTime = (double)(currentTime - lastTime) / SDL_GetPerformanceFrequency();
        if(deltaTime > 0.1)
        {
            deltaTime = 0.1;
        }
        lastTime = currentTime;

        // FPS draw into window title:
        frameTimer += deltaTime;
        frames++;
        if(frameTimer >= 1)
        {
            std::string title = "Simualtion | FPS: " + std::to_string(frames); 
            SDL_SetWindowTitle(window, title.c_str());
            frames = 0;
            frameTimer = 0;
        }
        // Spike detecting: (for optimization\debugging)
        if(hzMonitor)
        {
            if(frameMs > 1000 / (hzMonitor->refresh_rate) + 2.0) printf("Spike!!! %.2f ms\n", frameMs);
        }

        // Ball drawing and simulation:
        ball.update(ball, deltaTime, Gravity);
        drawer.drawBackground(renderer);
        drawer.drawBall(renderer, ball);

        SDL_RenderPresent(renderer);
    }
}