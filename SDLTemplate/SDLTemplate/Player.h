#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class Player : public GameObject
{
public:
	virtual void start() override;
	virtual void update() override;
	virtual void draw() override; 
private:
	int x;
	int y; 
	int width;
	int height;

	int speed;
	int defaultSpeed; 
	int burstSpeed; 

	SDL_Texture* texture; 
};

