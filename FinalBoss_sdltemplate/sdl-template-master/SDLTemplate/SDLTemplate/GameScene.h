#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "SnakeHead.h" 
#include "SnakeFood.h"
#include "util.h"
#include <vector> 
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	SnakeHead* snakehead;
	SnakeFood* snakefood;
	std::vector<SnakeFood*> GoodFood;
	void SpawnFood();
	void DespawnFood(SnakeFood* BodyGrow); 
};

