#include "Enemy.h"
#include "Scene.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
	//load texture
	texture = loadTexture("gfx/enemy.png");

	//initialize to avoid garbage values
	directionX = -1;
	directionY = 1;
	width = 0;
	height = 0;
	reloadTime = 60;
	currentReloadTime = 0;
	speed = 2;
	directionChangeTime = (rand() % 100) + 180;
	currentDirectionChangeTime = 0; 

	// Query the texture to set width 
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Enemy::update()
{
	x += directionX * speed;
	y += directionY * speed; 

	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}

	if (currentReloadTime > 0)
		currentReloadTime--;


	if (currentReloadTime == 0)
	{
		
		float dx;
		float dy;
		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);


		Bullet* bullet = new Bullet(x + width, y - 2 + height/2, dx, dy, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();

		currentReloadTime = reloadTime;
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
			break;
		}
	}
}

void Enemy::draw()
{
	blit(texture, x, y);
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player; 
}

void Enemy::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos; 
}
int Enemy::getPositionX()
{
	return x;
}
int Enemy::getPositionY()
{
	return y;
}

int Enemy::getHeight()
{
	return height;
}

int Enemy::getWidth()
{
	return width;
}