#include "GameScene.h"



GameScene::GameScene() 
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

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

	SpawnTime = 100;

	CurrSpawnTimePowerUp = 300;

	BossSpawnTime = 350; 

	BlockEnemySpawn = false; 

	WaveCountdown = 0; 

	SpawnTimePowerUp = 300;


	wallPaper = IMG_LoadTexture(app.renderer, "gfx/background.png") ;

	sound = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg"); 
	sound->volume = 10; 

	sound2 = SoundManager::loadSound("sound/PowerTime.ogg");
	sound2->volume = 20;

	sound3 = SoundManager::loadSound("sound/BossGetHit.ogg");
	sound3->volume = 15;

	sound4 = SoundManager::loadSound("sound/TomScream.ogg");
	sound4->volume = 20;

}

void GameScene::draw()
{
	Scene::draw();

	SDL_RenderPresent(app.renderer);

	drawText(700, 15, 255, 255, 255, TEXT_RIGHT, "POINTS: %03d", points);

	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, 530, 255, 0, 0, TEXT_CENTER, "GAME OVER!");
	}

}
#pragma region Functions

#pragma region Enemy spawn & despawn
void GameScene::SpawnOpp()
{
	if (currSpawnTime > 0 && BlockEnemySpawn == false) 
		currSpawnTime--;

	if (currSpawnTime <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			Enemy* enemy = new Enemy();
			this->addGameObject(enemy);
			enemy->setPlayerTarget(player);
			enemy->setPosition(350, -800 + (rand() % 300));
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
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}

}
#pragma endregion 
#pragma region Boss spawn & despawn 
void GameScene::SpawnBoss()
{
	if (WaveCountdown >= 15 && BlockEnemySpawn == false)
	{
		BlockEnemySpawn = true; 

		std::vector<Enemy*> enemiesToDespawn = spawnedEnemies;

		for (Enemy* enemy : enemiesToDespawn)
		{
			DeSpawnOpp(enemy);
		}

		// Clear the list just to be safe
		spawnedEnemies.clear();
	} 

	if (BossSpawnTime > 0 && BlockEnemySpawn == true ) 
		BossSpawnTime--;

	if (spawnedBoss.empty() && BossSpawnTime == 0)
	{
		Boss* boss = new Boss();
		this->addGameObject(boss);
		boss->setPlayerTarget(player); 
		boss->setPosition(300, -200);
		spawnedBoss.push_back(boss);

		// Lock spawn timer so we don't spawn again
		BossSpawnTime = -1;
	}

}

void GameScene::DespawnBoss(Boss* boss)
{
	WaveCountdown = 0; 
	BlockEnemySpawn = false;
	int index = -1;
	for (int i = 0; i < spawnedBoss.size(); i++)
	{
		if (boss == spawnedBoss[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		spawnedBoss.erase(spawnedBoss.begin() + index);
		delete boss;
	}

	

}
#pragma endregion
#pragma region Powerup spawners
void GameScene::SpawnPowerUp()
{

	if (CurrSpawnTimePowerUp > 0)
		CurrSpawnTimePowerUp--;

	if (CurrSpawnTimePowerUp <= 0)
	{
		Powerup* ExtraFire = new Powerup();
		this->addGameObject(ExtraFire);
		ExtraFire->setPosition(70 + (rand() % 600), -100);
		SimonPower.push_back(ExtraFire);
		CurrSpawnTimePowerUp = SpawnTimePowerUp;
	}


}

void GameScene::DespawnPowerUp(Powerup* ExtraFire)
{
	int index = -1;
	for (int i = 0; i < SimonPower.size(); i++)
	{
		if (ExtraFire == SimonPower[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		delete ExtraFire;
	}

}
#pragma endregion 

#pragma endregion 
void GameScene::update()
{ 
	Scene::update();
	SDL_RenderClear(app.renderer);
	SDL_RenderCopy(app.renderer, wallPaper, NULL, NULL);
	SpawnOpp();
	SpawnBoss(); 
	SpawnPowerUp();
	for (int i = 0; i < objects.size(); i++)
	{
		Powerup* ExtraFire = dynamic_cast<Powerup*>(objects[i]);
		if (ExtraFire != NULL)
		{
			int collision = checkCollision(
				player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
				ExtraFire->getPositionX(), ExtraFire->getPositionY(), ExtraFire->getWidth(), ExtraFire->getHeight());

			if (collision == 1)
			{
		
				SoundManager::playSound(sound2);

				DespawnPowerUp(ExtraFire);
				player->BoostFire();
				break;
			}
		}
	}
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

				if (collision == 1 && player->getIsAlive() == true)
				{
					SoundManager::playSound(sound);
					Explosion* bomba2 = new Explosion(player->getPositionX(), player->getPositionY());
					this->addGameObject(bomba2);
					player->doDeath();
				
					break;
				}
			}

			 if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(

						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);
					if (collision == 1)
					{ 
						
						SoundManager::playSound(sound);
						Explosion* bomba = new Explosion(currentEnemy->getPositionX(), currentEnemy->getPositionY());
						this->addGameObject(bomba);
						DeSpawnOpp(currentEnemy);

						WaveCountdown++;
						points++;
						break; 
					}
				}

				for (int i = 0; i < spawnedBoss.size(); i++)
				{
					Boss* boss = spawnedBoss[i];

					int collision = checkCollision(

						boss->getPositionX(), boss->getPositionY(), boss->getWidth(), boss->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1 && !boss->IsInvulnerable()) 
					{
						SoundManager::playSound(sound3);
						boss->GetHit();
						boss->GiveInvul(); 
						points++;
						if (boss->GetBossHealth() <= 0)
						{
							SoundManager::playSound(sound);
							Explosion* bomba2 = new Explosion(boss->getPositionX(), boss->getPositionY());
							SoundManager::playSound(sound4); 
							DespawnBoss(boss);
						
						}
						break; 
					}
				}

			}

			

		}
		
	}



	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (spawnedEnemies[i]->getPositionY() > SCREEN_WIDTH) 
		{
			Enemy* EraseOpp = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);
			delete EraseOpp;
			break;
		}
	}
}







 
