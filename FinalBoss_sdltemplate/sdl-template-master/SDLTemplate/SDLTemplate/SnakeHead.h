#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h" 
#include "SoundManager.h"

class SnakeHead :
    public GameObject
{
	void start();
	void update();
	void draw();
	bool getIsAlive(); 
	void KillSnake(); 
	int getPosX();
	int getPosY();
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

