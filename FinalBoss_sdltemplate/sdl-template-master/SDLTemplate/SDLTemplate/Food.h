#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h" 
#include "SoundManager.h"
class Food : public GameObject
{
public:

	Food();
	~Food();
	void start() override;
	void update()override;
	void draw()override;
	void setPosition(int xPos, int yPos);
	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

private:
	int x;
	int y;
	int width;
	int height;
	SDL_Texture* texture;
};


