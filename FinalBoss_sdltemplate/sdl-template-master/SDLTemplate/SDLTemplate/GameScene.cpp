#include "GameScene.h"

GameScene::GameScene()
{
	snakehead = new SnakeHead();
	snakehead->start();
	addGameObject(snakehead);
	points = 0;
	Highscore = 0; 

	DeadSound = SoundManager::loadSound("sound/Fahh.ogg");
	FoodEaten = SoundManager::loadSound("sound/PowerTime.ogg");

	SoundManager::loadMusic("sound/DiddyBlud.ogg"); 
	SoundManager::playMusic(1); 
	Mix_VolumeMusic(20);

	SpawnFood();
}

GameScene::~GameScene()
{
	delete snakehead;
}

void GameScene::start()
{
	Scene::start();
	initFonts();
	
}

void GameScene::draw()
{
	Scene::draw();

	snakehead->draw();
	for (auto segment : bodies)
		segment->draw();

	SDL_RenderPresent(app.renderer);

	drawText(215, 20, 255, 255, 255, TEXT_RIGHT, "POINTS: %03d", points);

	drawText(985, 20, 255, 255, 255, TEXT_RIGHT, "HIGHEST SCORE: %03d", Highscore);

	if (snakehead->getPlayerStart() == true) 
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 255, 0, 0, TEXT_CENTER, "PRESS E TO START");
	}

	if (!snakehead->getIsAlive())
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 0, 0, TEXT_CENTER, "GAME OVER!");

		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 255, 255, 255, TEXT_CENTER,
			"PRESS R TO RESTART"); 
	}
}


void GameScene::update()
{

	Scene::update();

	snakehead->update();

	for (auto segment : bodies) {
		segment->update();
	}

	for (int i = 0; i < objects.size(); i++)
	{
		SnakeBody* snakebody = dynamic_cast<SnakeBody*>(objects[i]);
		if (snakebody != NULL)
		{
			int collision = checkCollision(
				snakehead->getPositionX() * CELL_SIZE,
				snakehead->getPositionY() * CELL_SIZE,
				snakehead->getWidth(), snakehead->getHeight(),

				snakebody->getX() * CELL_SIZE,
				snakebody->getY() * CELL_SIZE,
				snakebody->getWidth(), snakebody->getHeight());

			if (collision == 1 && snakehead->getIsAlive() == true)
			{
				SoundManager::playSound(DeadSound);
				snakehead->KillSnake(); 
				break;

			}
		}
		SnakeFood* BodyGrow = dynamic_cast<SnakeFood*>(objects[i]);
		if (BodyGrow != NULL)
		{
			int collision = checkCollision(
				snakehead->getPositionX() * CELL_SIZE,
				snakehead->getPositionY() * CELL_SIZE,
				snakehead->getWidth(), snakehead->getHeight(),

				BodyGrow->getPositionX() * CELL_SIZE,
				BodyGrow->getPositionY() * CELL_SIZE,
				BodyGrow->getWidth(), BodyGrow->getHeight());

			if (collision == 1)
			{
				SoundManager::playSound(FoodEaten);
				points++;
				DespawnFood(BodyGrow);
				SpawnFood();
				addSegment();
				break;

			}
			
				// ---- BODY overlaps food (undesired spawn) → respawn ----
				for (auto SnakeBody : bodies)
				{
					int bodyCollision = checkCollision(
						SnakeBody->getX() * CELL_SIZE,
						SnakeBody->getY() * CELL_SIZE,
						SnakeBody->getWidth(), SnakeBody->getHeight(),

						BodyGrow->getPositionX() * CELL_SIZE,
						BodyGrow->getPositionY() * CELL_SIZE,
						BodyGrow->getWidth(), BodyGrow->getHeight());

					if (bodyCollision == 1)
					{
					
						std::cout << "Food & body collided" << std::endl;
						DespawnFood(BodyGrow);
						SpawnFood();
						break;
					}



				}
		}
	}
	if (!snakehead->getIsAlive())
	{
		Mix_HaltMusic();

		if (points > Highscore) {
			Highscore = points;  // update the stored high score
		}

		if (app.keyboard[SDL_SCANCODE_R])
		{
			gameRestart(); 
		}
	}
}

void GameScene::gameRestart()
{
	// Reset points
	
	points = 0; 

	// Delete old head & segments
	delete snakehead;
	for (auto b : bodies)
		delete b;
	bodies.clear();

	// Delete all food
	for (auto f : GoodFood)
		delete f;
	GoodFood.clear();

	// Clear all game objects (important!)
	objects.clear();

	// Respawn head & add it to objects
	snakehead = new SnakeHead();
	snakehead->start();
	addGameObject(snakehead);


	// Respawn first food
	SpawnFood();
	if (Highscore >= 100)
	{
		SoundManager::loadMusic("sound/Remember me.ogg");
		SoundManager::playMusic(1);
		Mix_VolumeMusic(20);
	}
	else
	{
		SoundManager::loadMusic("sound/DiddyBlud.ogg");
		SoundManager::playMusic(1);
		Mix_VolumeMusic(20);
	}


	// Add back startup message
	if (snakehead->getPlayerStart() == true)
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 0, 0, 0, TEXT_CENTER, "PRESS E TO START");
	}
}

void GameScene::SpawnFood()
{
	SnakeFood* BodyGrow = new SnakeFood();
	this->addGameObject(BodyGrow);

	// Tile-based spawn
	int gridX = 1 + (rand() % (GRID_COLUMNS - 2));
	int gridY = 1 + (rand() % (GRID_ROWS - 2));

	BodyGrow->setPosition(gridX, gridY);

	GoodFood.push_back(BodyGrow);
}

void GameScene::DespawnFood(SnakeFood* BodyGrow)
{
	int index = -1;

	for (int i = 0; i < GoodFood.size(); i++)
	{
		if (BodyGrow == GoodFood[i])   
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		GoodFood.erase(GoodFood.begin() + index);
		delete BodyGrow;              
	}

}

// --- Add a new segment ---
void GameScene::addSegment()
{
	SnakeBody* lastSegment = nullptr;
	if (!bodies.empty())
		lastSegment = bodies.back();

	int newX, newY;
	if (lastSegment)
	{
		newX = lastSegment->getPrevX();
		newY = lastSegment->getPrevY();
	}
	else
	{
		// First segment follows head
		newX = snakehead->getPrevX();
		newY = snakehead->getPrevY();
	}

	SnakeBody* newSegment = new SnakeBody(newX, newY);
	if (lastSegment)
		newSegment->setFollowTarget(lastSegment);

	else
		newSegment->setHeadTarget(snakehead);
		newSegment->start();
		addGameObject(newSegment);
		bodies.push_back(newSegment);
}

