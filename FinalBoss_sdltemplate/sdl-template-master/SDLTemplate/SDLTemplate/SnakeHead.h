#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h" 
#include "SoundManager.h"
#include <vector> 
#include "SnakeBody.h"


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
	int getPrevX();
	int getPrevY();
	bool getPlayerStart();

private:
	SDL_Texture* texture; 
	int x, y;
	int prevX, prevY; 
	int width, height; 
	float MoveTimer,CurrMoveTimer; 
	float dirX, dirY;
	float InputDelay, CurrInputTimer;
	bool PlayerStart; 
	bool isAlive; 
	
	Mix_Chunk* DeadSound;
	Mix_Chunk* TurnNoise; 
};

