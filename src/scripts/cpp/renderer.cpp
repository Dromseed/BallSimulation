#include "renderer.hpp"

// Calculation the circle to draw the ball:
static void drawCircle(SDL_Renderer* r, int cx, int cy, int radius)
{
    for(int w = 0; w < radius * 2; ++w)
    {
        for(int h = 0; h < radius * 2; ++h)
        {
            int dx = radius - w;
            int dy = radius - h;
            if(dx * dx + dy * dy <= radius * radius)
            {
                SDL_RenderPoint(r, cx + dx, cy + dy);
            }
        }
    }    
}
// Drawing background:
void Renderer::drawBackground(SDL_Renderer* r) 
{
    // Background color (grey): 
    SDL_SetRenderDrawColor(r, 180, 180, 180, 255);
    SDL_RenderClear(r);
}
// Drawaing a ball: 
void Renderer::drawBall(SDL_Renderer* r, const Ball& b)
{
    // Circle color (black):
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    drawCircle(r, (int)b.x, (int)b.y, b.radius);
}