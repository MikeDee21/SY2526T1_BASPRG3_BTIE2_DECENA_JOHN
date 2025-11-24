#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "SnakeHead.h" 
#include "SnakeFood.h"
#include "SnakeBody.h"
#include "util.h"
#include <vector> 
#include "text.h"
#include "SoundManager.h"
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
	void gameRestart();

	
private:

	int points, Highscore; 

	Mix_Chunk* FoodEaten;
	Mix_Chunk* DeadSound; 
	SnakeHead* snakehead;

	SnakeFood* snakefood;
	std::vector<SnakeFood*> GoodFood;

	SnakeBody* snakebody; 
	std::vector<SnakeBody*>bodies;
	
	void SpawnFood();
	void DespawnFood(SnakeFood* BodyGrow); 
	void addSegment();
};

