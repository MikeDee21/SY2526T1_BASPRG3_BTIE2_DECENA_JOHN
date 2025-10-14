#include "GameScene.h"



GameScene::GameScene() 
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	//enemy = new Enemy();
	//this->addGameObject(enemy);
	//enemy->setPlayerTarget(player); 

	points = 0; 
}

GameScene::~GameScene()
{
	delete player; 
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here
	initFonts();
	currSpawnTime = 300;
	SpawnTime = 300;
	wallPaper = IMG_LoadTexture(app.renderer, "gfx/background.png") ;

	
	
}

void GameScene::draw()
{
	Scene::draw();

	SDL_RenderPresent(app.renderer);

	drawText(110, 20, 255, 255,255, TEXT_CENTER, "POINTS: %03d",points); 

	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "GAME OVER!"); 
	}
}

void GameScene::update()
{
	Scene::update();
	SDL_RenderClear(app.renderer); 
	SDL_RenderCopy(app.renderer, wallPaper, NULL, NULL);
	SpawnOpp(); 
	for (int i = 0; i < objects.size(); i++)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]); 
		if (bullet != NULL)
		{
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
			player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(), 
			bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight() 
				);

				if (collision == 1)
				{
					player->doDeath(); 
					break;  
				}
			}

			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(

						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(),currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);
					if (collision == 1)
					{
						Explosion* bomba = new Explosion (currentEnemy->getPositionX(), currentEnemy->getPositionY()); 
						this->addGameObject(bomba);
						bomba->start(); 

						DeSpawnOpp(currentEnemy);

						points++; 
						break;  
					}
				}
			}
		}
	}
	
}

void GameScene::SpawnOpp()
{
	if (currSpawnTime > 0)
		currSpawnTime--;

	if (currSpawnTime <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			Enemy* enemy = new Enemy();
			this->addGameObject(enemy);
			enemy->setPlayerTarget(player);
			enemy->setPosition(2000, 300 + (rand() % 300));
			spawnedEnemies.push_back(enemy);
			currSpawnTime = SpawnTime;
		}
	}
}

void GameScene::DeSpawnOpp(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (enemy == spawnedEnemies[i])
		{
			index = 1;
			break; 
		}
	}

	if (index != -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}
