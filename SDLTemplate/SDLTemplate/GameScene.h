#pragma once
#include "Scene.h"
#include "GameObject.h"
#include"Player.h"
#include "Enemy.h"
#include <vector> 
#include "text.h" 

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	Player* player; 
	Enemy* enemy; 

	//spawn code
	float SpawnTime;
	float currSpawnTime; 
	std::vector<Enemy*> spawnedEnemies;
	std::vector<Enemy*>Explosion;
	void SpawnOpp(); 
	void DeSpawnOpp(Enemy* enemy); 
	SDL_Texture* wallPaper; 

	int points; 
};

