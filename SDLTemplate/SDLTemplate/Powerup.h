#pragma once
#include "GameObject.h"
class Powerup : public GameObject
{ 
	public:

	Powerup();
	~Powerup();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() override;
	virtual void setPosition(int xPos, int yPos);  
	int getPositionX();
	int getPositionY();
	int getWidth(); 
	int getHeight();

private:
	int x;
	int y;
	int width;
	int height;
	int duration;
	int speed; 
	float directionY;
	SDL_Texture* texture;
}; 
