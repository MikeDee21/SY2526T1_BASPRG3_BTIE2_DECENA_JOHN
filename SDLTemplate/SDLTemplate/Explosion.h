#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "draw.h"

class Explosion:public GameObject
{
public:
	Explosion(int x, int y, int width, int height);
	~Explosion(); 
	virtual void start() override;
	virtual void update() override;
	virtual void draw() override;

private:
	int x;
	int y; 
	int width;
	int height; 
	int duration;
	int MaxDuration; 
	SDL_Texture* texture;

};

