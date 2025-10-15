#include "Explosion.h"



Explosion::Explosion(int x, int y)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	duration = 200;
	MaxDuration = duration;
}

Explosion::~Explosion()
{
}

void Explosion::start()
{
	texture = loadTexture("gfx/explosion.png");
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Explosion::update()
{
	duration--;
	if (duration == 0)
	{
		delete this; 	
	}
}

void Explosion::draw()
{
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_RenderCopy(app.renderer, texture, NULL, &destRect);

}

