#include "SnakeHead.h"
void SnakeHead::start()
{
	texture = loadTexture("gfx/SnakeHead.jpg");

    // Start in the middle of the grid
    x = GRID_COLUMNS / 2;
    y = GRID_ROWS / 2;

    // Sprite dimensions (pixels)
    width = 50;
    height = 50;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void SnakeHead::update()
{

}

void SnakeHead::draw() 
{
    SDL_Rect dest;
    dest.x = x * CELL_SIZE + (CELL_SIZE - width) / 2;
    dest.y = y * CELL_SIZE + (CELL_SIZE - height) / 2;
    dest.w = width;
    dest.h = height;

    SDL_RenderCopy(app.renderer, texture, NULL, &dest); 
}