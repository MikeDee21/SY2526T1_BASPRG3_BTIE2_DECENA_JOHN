#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "Bullet.h"
class Bullet : public GameObject
{
public:
	Bullet(float positionX, float positionY, float directionX, float directionY, float speed);
	virtual void start() override;
	virtual void update() override;
	virtual void draw() override; 
	float getPositionX();
	float getPositionY();
	float getWidth();
	float getHeight(); 
private:
	SDL_Texture* texture; 
	int x;
	int y;
	int width;
	int height;
	int speed;
	float directionX;
	float directionY;
};

