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
	x = 350;
	y = 550;
	width = 0; 
	height = 0;
	reloadTime = 8;
	currentReloadTime = 0; 
	defaultSpeed = 2;
	speed = defaultSpeed; 
	burstSpeed = 7;   
	isAlive = true; 
	boostFire = 1; 
	SecReloadTime = 15; 

	// Query the texture to set width 
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);  

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg"); 
}

void Player::update()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionY() > SCREEN_HEIGHT)
		{
			Bullet* bulletToErase = bullets[i]; 
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
			break; 
		}
	}
	if (!isAlive) return;
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

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0 && boostFire == 1)
	{
		SoundManager::playSound(sound); 
		Bullet* bullet = new Bullet(x + width/2, y + height/2, 0, -1, 10,Side::PLAYER_SIDE); 
		getScene()->addGameObject(bullet);
		bullet->start();

		
		currentReloadTime = reloadTime; 
	}
	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0 && boostFire == 2)
	{
		SoundManager::playSound(sound); 
		Bullet* bullet = new Bullet(x + width, y, 0, -1, 10, Side::PLAYER_SIDE); 
		bullets.push_back(bullet); 
		getScene()->addGameObject(bullet);
		bullet->start(); 

		Bullet* bullet2 = new Bullet(x - width/6, y, 0, -1, 10, Side::PLAYER_SIDE); 
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet2);
		bullet2->start();

		currentReloadTime = SecReloadTime;    
	} 

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0 && boostFire >= 3)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width / 2, y + height / 2, 0, -1, 10, Side::PLAYER_SIDE);
		getScene()->addGameObject(bullet);
		bullet->start();

		SoundManager::playSound(sound);
		Bullet* bullet2 = new Bullet(x + width, y, 0, -1, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet2);
		bullet2->start();

		SoundManager::playSound(sound);
		Bullet* bullet3 = new Bullet(x - width / 6, y, 0, -1, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet3);
		getScene()->addGameObject(bullet3);
		bullet3->start();

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
	
}

void Player::draw()
{
	if (!isAlive) return;

	blit(texture, x, y); 
}

int Player::getPositionX()
{
	return x;
}
int Player::getPositionY()
{
	return y; 
}

int Player::getHeight()
{
	return height; 
}

int Player::getWidth()
{
	return width; 
}

bool Player::getIsAlive()
{
	return isAlive;  
}

void Player::doDeath()
{
	isAlive = false; 
}

void Player::BoostFire()
{
	boostFire++;   
}
