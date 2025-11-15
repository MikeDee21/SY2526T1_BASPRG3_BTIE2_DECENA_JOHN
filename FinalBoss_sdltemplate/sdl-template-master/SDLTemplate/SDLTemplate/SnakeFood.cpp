#include "SnakeFood.h"
SnakeFood::SnakeFood()
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height; 
}

SnakeFood::~SnakeFood()
{

}

void SnakeFood::start()
{
    texture = loadTexture("gfx/Fud.jpg");
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
  
}

void SnakeFood::update()
{

}

void SnakeFood::draw()
{
    SDL_Rect dest;
    dest.x = x * CELL_SIZE;
    dest.y = y * CELL_SIZE; 
    dest.w = width;  
    dest.h = height; 

    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void SnakeFood::setPosition(int xPos, int yPos)
{
    this->x = xPos;
    this->y = yPos; 
}

int SnakeFood::getPositionX()
{
    return x;
}

int SnakeFood::getPositionY()
{
    return y;
}

int SnakeFood::getWidth()
{
    return width;
}

int SnakeFood::getHeight()
{
    return height;
}
