#include "Player.h"

void Player::start()
{
	//load texture
	texture = loadTexture("gfx/player.png");

	//initialize to avoid garbage values
	x = 100;
	y = 100;
	width = 0; 
	height = 0;


	defaultSpeed = 3;
	speed = defaultSpeed; 
	burstSpeed = 5;   
	
	// Query the texture to set width 
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);  
}

void Player::update()
{
	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}


	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_W])
	{
		x += speed;
	}


	if (app.keyboard[SDL_SCANCODE_LSHIFT]) 
	{
		speed = burstSpeed; 
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = defaultSpeed; 
	}
}

void Player::draw()
{
	blit(texture, x, y); 
}
