#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	snakehead = new SnakeHead();
	this->addGameObject(snakehead); 

}

GameScene::~GameScene()
{

}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();

}
