#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "Bullet.h" 
#include <vector> 
#include "util.h"
#include "Player.h"
class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy(); 
	virtual void start() override;
	virtual void update() override;
	virtual void draw() override;
	virtual void setPlayerTarget(Player* player);
	virtual void setPosition(int xPos, int yPos);
private:
	int x;
	int y;
	float directionX;
	float directionY; 
	float directionChangeTime;
	float currentDirectionChangeTime;
	int width;
	int height;

	int speed;
	float reloadTime;
	float currentReloadTime;
	std::vector<Bullet*>bullets;
	Player* playerTarget; 

	SDL_Texture* texture;
};

