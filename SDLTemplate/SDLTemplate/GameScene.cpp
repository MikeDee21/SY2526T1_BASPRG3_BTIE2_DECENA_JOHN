#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	//enemy = new Enemy();
	//this->addGameObject(enemy);
	//enemy->setPlayerTarget(player); 

}

GameScene::~GameScene()
{
	delete player; 
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here
	currSpawnTime = 300;
	SpawnTime = 300;
	for (int i = 0; i < 3; i++)
	{
		SpawnOpp();
	}
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();
	if (currSpawnTime > 0)
		currSpawnTime--; 

	if (currSpawnTime <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			SpawnOpp();
			currSpawnTime = SpawnTime;
		}
	} 
	
}

void GameScene::SpawnOpp()
{

	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);
	enemy->setPosition(2000, 300 + (rand() % 300));
	spawnedEnemies.push_back(enemy);
	currSpawnTime = SpawnTime;
}
