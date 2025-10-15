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
	//spawn code
	
	
	float SpawnTime;
	float currSpawnTime; 
	std::vector<Enemy*> spawnedEnemies;
	void SpawnOpp(); 
	void DeSpawnOpp(Enemy* enemy); 

	//Powerup spawn code
	float SpawnTimePowerUp;
	float CurrSpawnTimePowerUp;
	std::vector<Powerup*> SimonPower; 
	void SpawnPowerUp();
	void DespawnPowerUp(Powerup* ExtraFire); 

	SDL_Texture* wallPaper; 
	Mix_Chunk* sound;
	Mix_Chunk* sound2; 
	int points; 
};

