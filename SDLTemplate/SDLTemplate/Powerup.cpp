#include "Powerup.h"

Powerup::Powerup()
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	duration = 500;

}

Powerup::~Powerup()
{
}

void Powerup::start()
{
	texture = loadTexture("gfx/Powerup.png"); 
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	directionY = -1;
	speed = 2;
}

void Powerup::update()
{
	y -= directionY * speed; 

	duration--; 
	if (duration == 0)
	{
		delete this;
	}
}

void Powerup::draw()
{
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_RenderCopy(app.renderer, texture, NULL, &destRect); 
}
void Powerup::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}
int Powerup::getPositionX()
{
	return x;
}
int Powerup::getPositionY()
{
	return y;
}

int Powerup::getHeight()
{
	return height;
}

int Powerup::getWidth()
{
	return width;
}