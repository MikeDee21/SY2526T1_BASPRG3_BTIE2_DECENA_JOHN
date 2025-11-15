#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h" 


class SnakeFood : public GameObject
{
public:

	SnakeFood();
	~SnakeFood();
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
	SDL_Texture* texture;
};

