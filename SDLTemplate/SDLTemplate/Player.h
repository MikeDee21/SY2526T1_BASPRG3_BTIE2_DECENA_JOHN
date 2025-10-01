#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "Bullet.h" 
#include <vector> 

class Player : public GameObject
{
public:
	~Player(); 
	virtual void start() override;
	virtual void update() override;
	virtual void draw() override; 

	int getPositionX();
	int getPositionY();
private:
	int x;
	int y; 
	int width;
	int height;

	int speed;
	float reloadTime;
	float currentReloadTime; 
	float SecReloadTime; 
	int defaultSpeed; 
	int burstSpeed; 
	std::vector<Bullet*>bullets; 

	SDL_Texture* texture; 
};

