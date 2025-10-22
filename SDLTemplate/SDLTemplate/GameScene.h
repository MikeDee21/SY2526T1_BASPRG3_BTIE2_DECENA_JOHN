#pragma once
#include "Scene.h"
#include "GameObject.h"
#include"Player.h"
#include "Enemy.h"
#include <vector> 
#include "text.h" 
#include "Explosion.h" 
#include "SoundManager.h"
#include "Powerup.h"
#include "Boss.h"

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
	Powerup* ExtraFire;
	Boss* boss;
	
	//spawn code
	float SpawnTime;
	float currSpawnTime; 
	std::vector<Enemy*> spawnedEnemies;
	void SpawnOpp(); 
	void DeSpawnOpp(Enemy* enemy); 

	//Boss spawn 
	int WaveCountdown; 
	float BossSpawnTime;
	bool BlockEnemySpawn; 
	std::vector<Boss*> spawnedBoss;
	void SpawnBoss();
	void DespawnBoss(Boss* boss);

	//Powerup spawn code 
	float SpawnTimePowerUp;
	float CurrSpawnTimePowerUp;
	std::vector<Powerup*> SimonPower; 
	void SpawnPowerUp();
	void DespawnPowerUp(Powerup* ExtraFire); 

	SDL_Texture* wallPaper; 
	Mix_Chunk* sound;
	Mix_Chunk* sound2; 
	Mix_Chunk* sound3;
	Mix_Chunk* sound4; 
	int points; 
};

