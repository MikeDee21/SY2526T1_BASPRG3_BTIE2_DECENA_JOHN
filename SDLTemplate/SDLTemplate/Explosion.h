#pragma once
#include "GameObject.h"

class Explosion :
    public GameObject
{
public:
	Explosion(int x, int y);
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

