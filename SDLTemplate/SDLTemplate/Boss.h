#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "Bullet.h" 
#include <vector> 
#include "util.h"
#include "Player.h"
#include <cmath> 

enum class FireMode
{
	STRAIGHT, SPIRAL, TWIN_SPIRAL, NONE
};

class Boss : public GameObject
{
public:
	Boss();
	~Boss();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() override;
	virtual void setPlayerTarget(Player* player); 
	virtual void setPosition(int xPos, int yPos);

	int getPositionX();
	int getPositionY();
	int getHeight();
	int getWidth();
	void GetHit(); 
	int GetBossHealth(); 
	FireMode GetMode();
	void GiveInvul();
	bool IsInvulnerable();
	void UpdateInvul();
	
private:
	void fireStraight();
	void fireSpiral();
	void fireTwinSpiral(); 
	FireMode currentFireMode;  // which mode is active
	int fireTimer;             // counts frames for current mode
	int fireDuration;          // frames for each mode
	int cycleCooldown;                // optional pause between modes
	bool isFiring;

	// Spiral-specific
	float spiralAngle;                  // angle for spiral bullets
	float spiralCone;                  // for twin spiral, cone width in degrees
	bool coneShrinking;               // toggles cone shrinking/growing

	int x;
	int y;
	float directionX;
	float directionY;
	float directionChangeTime;
	float currentDirectionChangeTime;
	int width;
	int height;
	int BossHealth; 
	int CurrBossHealth; 
	int speed;
	float reloadTime;
	float currentReloadTime;
	bool BossAlive; 
	int BossShotCooldown;
	int BossCurrShotTime;
	int invincibilityTimer;   // counts down every frame
	int invulDuration; // frames of invulnerability after hit 

	// Movement variables
	int entrySpeed;    // speed while entering from top
	bool hasEntered;    // flag to know if entry phase is done
	float timeMotion;             // time parameter for figure-8 motion
	float figure8Width;   // horizontal size of the figure-8
	float figure8Height;  // vertical size of the figure-8
	float centerX, centerY;     // center point for figure-8 motion
	int currentModeIndex;    // cycle through firing modes   
	std::vector<Bullet*>bullets;
	Player* playerTarget;

	SDL_Texture* texture;
};

