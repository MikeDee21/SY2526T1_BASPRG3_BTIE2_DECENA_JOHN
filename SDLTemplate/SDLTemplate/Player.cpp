#include "Player.h"
#include "Scene.h"

Player::~Player()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear(); 
}

void Player::start()
{
	//load texture
	texture = loadTexture("gfx/player.png");
	
	//initialize to avoid garbage values
	x = 100;
	y = 100;
	width = 0; 
	height = 0;
	reloadTime = 8;
	SecReloadTime = 25; 
	currentReloadTime = 0; 
	defaultSpeed = 2;
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

	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}
	
	if (currentReloadTime > 0)
		currentReloadTime--; 

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
	{
		Bullet* bullet = new Bullet(x + width, y + height/2, 1, 0, 10); 
		getScene()->addGameObject(bullet);
		bullet->start(); 

		currentReloadTime = reloadTime; 
	}
	if (app.keyboard[SDL_SCANCODE_G] && currentReloadTime == 0)
	{
		Bullet* bullet = new Bullet(x + width, y, 1, 0, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();

		Bullet* bullet2 = new Bullet(x + width, y + height, 1, 0, 10);
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet2);
		bullet2->start();

		currentReloadTime = SecReloadTime; 
	}

	if (app.keyboard[SDL_SCANCODE_LSHIFT]) 
	{
		speed = burstSpeed; 
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = defaultSpeed; 
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase; 
			break; 
		}
	}
}

void Player::draw()
{
	blit(texture, x, y); 
}
