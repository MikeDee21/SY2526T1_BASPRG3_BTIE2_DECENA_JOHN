#include "Food.h"


Food::Food()
{
	this->x = GRID_COLUMNS / 2 + 1;  // middle of the grid
	this->y = GRID_ROWS / 2 + 1;
	this->width = CELL_SIZE;
	this->height = CELL_SIZE;
}

Food::~Food()
{

}

void Food::start()
{
	texture = loadTexture("gfx/fud.jpg");
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

}

void Food::update()
{

}

void Food::draw()
{
	SDL_Rect dest;
	dest.x = x * CELL_SIZE + (CELL_SIZE - width) / 2; 
	dest.y = y * CELL_SIZE + (CELL_SIZE - height) / 2; 
	dest.w = width;
	dest.h = height;

	SDL_RenderCopy(app.renderer, texture, NULL, &dest); 
}

void Food::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos; 
}

int Food::getPositionX()
{
	return x;
}

int Food::getPositionY()
{
	return y;
}

int Food::getWidth()
{
	return width;
}

int Food::getHeight()
{
	return height;
}
