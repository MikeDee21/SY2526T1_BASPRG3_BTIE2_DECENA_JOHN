#include "Boss.h"
#include "Scene.h"

Boss::Boss() {}
Boss::~Boss()
{
    // Delete all bullets spawned by the boss (if not already deleted by the scene)
    for (Bullet* b : bullets)
        delete b;
    bullets.clear();
}

void Boss::start()
{
    texture = loadTexture("gfx/Boss.png");

    width = 0;
    height = 0; 
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    // Boss stats
    BossHealth = 75;
    BossShotCooldown = 12; // frames between shots (adjust for difficulty)
    BossCurrShotTime = 0;
    invulDuration = 5; 
    invincibilityTimer = 0;
    speed = 1; 
    entrySpeed = speed;
    hasEntered = false;
    x = 300;
    y = -height;

    timeMotion = 0;
    figure8Width = 150;
    figure8Height = 100;
    centerX = 0;
    centerY = 0;

    // Fire system
    fireTimer = 0;
    fireDuration = 300;    // frames for each mode (~5 seconds at 60fps)
    cycleCooldown = 180;   // optional pause (~3 seconds)
    currentModeIndex = 0;
    currentFireMode = FireMode::STRAIGHT;
    isFiring = false;

    // Spiral-specific
    spiralAngle = 0.0f;
    spiralCone = 45.0f;
    coneShrinking = true;
}

void Boss::update()
{
    UpdateInvul(); 
    // --- ENTRY PHASE ---
    if (!hasEntered)
    {
        y += entrySpeed;
        if (y >= 100)
        {
            hasEntered = true;
            centerX = x;
            centerY = y;
            timeMotion = 0;

            fireTimer = 0;
            currentModeIndex = 0;
            currentFireMode = FireMode::STRAIGHT;
            isFiring = true;
            spiralAngle = 0;
            spiralCone = 45;
            coneShrinking = true;

            BossCurrShotTime = 0; // ready to fire immediately
        }
    }
    else
    {
        // --- FIGURE-8 MOVEMENT ---
        timeMotion += 0.05f;
        x = centerX + figure8Width * sin(timeMotion);
        y = centerY + figure8Height * sin(2 * timeMotion) / 2;

        // --- FIRING SYSTEM ---
        fireTimer++;

        // Switch mode after fireDuration + cycleCooldown
        if (fireTimer >= fireDuration + cycleCooldown)
        {
            fireTimer = 0;
            currentModeIndex = (currentModeIndex + 1) % 3;
            switch (currentModeIndex)
            {
            case 0: currentFireMode = FireMode::STRAIGHT; break;
            case 1: currentFireMode = FireMode::SPIRAL; break;
            case 2: currentFireMode = FireMode::TWIN_SPIRAL; break;
            }
            BossCurrShotTime = 0; // reset for new mode
        }

        if (fireTimer < fireDuration) // only during active firing
        {
            isFiring = true;

            // decrement per-frame shot timer
            if (BossCurrShotTime > 0)
                BossCurrShotTime--;

            // fire when timer reaches 0
            if (BossCurrShotTime <= 0)
            {
                switch (currentFireMode)
                {
                case FireMode::STRAIGHT: fireStraight(); break;
                case FireMode::SPIRAL: fireSpiral(); break;
                case FireMode::TWIN_SPIRAL: fireTwinSpiral(); break;
                }

                // reset per-frame cooldown for continuous stream
                // 10 bullets/sec → every 6 frames
                BossCurrShotTime = 6;
            }
        }
        else
        {
            isFiring = false;
        } 
    }

}

void Boss::draw()
{
    SDL_Rect dstRect = { (int)x, (int)y, width, height };
    SDL_RenderCopy(app.renderer, texture, NULL, &dstRect);
}

void Boss::setPlayerTarget(Player* player) 
{ 
    playerTarget = player; 
}

void Boss::setPosition(int xPos, int yPos) 
{ 
    x = xPos; y = yPos;
}
void Boss::GetHit() 
{ 
    BossHealth--; 
}

int Boss::getPositionX() 
{ 
    return (int)x;
}

int Boss::getPositionY() 
{ 
 return (int)y; 
}

int Boss::getHeight() 
{ 
    return height;
}

int Boss::getWidth() 
{ 
    return width; 
}

int Boss::GetBossHealth() 
{
    return BossHealth;
}

FireMode Boss::GetMode() 
{ 
    return currentFireMode;
}

void Boss::GiveInvul()
{
    invincibilityTimer = invulDuration;
}

bool Boss::IsInvulnerable()
{
    return invincibilityTimer > 0;;
}

void Boss::UpdateInvul()
{
    if (invincibilityTimer > 0)
        invincibilityTimer--; 
}

// --- FIRING METHODS ---
void Boss::fireStraight()
{
    Bullet* b = new Bullet(x + width / 2, y + height, 0, 5, 10, Side::ENEMY_SIDE);
    getScene()->addGameObject(b);
    bullets.push_back(b); 
}

void Boss::fireSpiral()
{
         float speed = 2.5f; 
        int bulletsPerShot = 4;
        float angleStep = 30.0f; // degrees between bullets

        for (int i = 0; i < bulletsPerShot; i++)
        {
            float angle = spiralAngle + i * angleStep;
            float rad = angle * (M_PI / 180.0f);
            float dirX = cos(rad) * speed;
            float dirY = sin(rad) * speed;

            Bullet* b = new Bullet(x + width / 2, y + height / 2, dirX, dirY, speed, Side::ENEMY_SIDE);
            getScene()->addGameObject(b);
        }

        spiralAngle += 5.0f; // rotate the spiral each shot
}

void Boss::fireTwinSpiral()
{
   
        float speed = 2.5f; 
        int bulletsPerSpiral = 3;
        float coneHalf = spiralCone / 2.0f;

        for (int i = 0; i < bulletsPerSpiral; i++)
        {
            float angleOffset = -coneHalf + i * (spiralCone / (bulletsPerSpiral - 1));

            float rad1 = (spiralAngle + angleOffset) * (M_PI / 180.0f);
            float rad2 = (spiralAngle - angleOffset) * (M_PI / 180.0f);

            Bullet* b1 = new Bullet(x + width / 2, y + height / 2, cos(rad1) * speed, sin(rad1) * speed, speed, Side::ENEMY_SIDE);
            Bullet* b2 = new Bullet(x + width / 2, y + height / 2, cos(rad2) * speed, sin(rad2) * speed, speed, Side::ENEMY_SIDE);

            getScene()->addGameObject(b1);
            getScene()->addGameObject(b2); 
        }

        // slowly rotate the spirals
        spiralAngle += 5.0f;

        // adjust cone
        if (coneShrinking)
        {
            spiralCone -= 1.0f;
            if (spiralCone <= 10.0f) coneShrinking = false;
        }
        else
        {
            spiralCone += 1.0f;
            if (spiralCone >= 45.0f) coneShrinking = true; 
        }

}




 
