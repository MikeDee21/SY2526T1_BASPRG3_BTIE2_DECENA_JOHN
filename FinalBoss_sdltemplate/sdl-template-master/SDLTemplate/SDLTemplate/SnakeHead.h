#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h" 
#include "SoundManager.h"
#include <vector> 

class SnakeHead : public GameObject
{
public:
	void start();
	void update();
	void draw();
	bool getIsAlive(); 
	void KillSnake(); 
	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

private:
	SDL_Texture* texture; 
	int x;
	int y;
	int width;
	int height; 
	float MoveTimer;
	float CurrMoveTimer; 
	float dirX;
	float dirY;
	bool isAlive; 
	Mix_Chunk* DeadSound;
};

