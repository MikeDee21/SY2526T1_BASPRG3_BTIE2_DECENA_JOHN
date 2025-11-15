#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	snakehead = new SnakeHead();
	this->addGameObject(snakehead); 
	SpawnFood(); 

	points = 0; 
}

GameScene::~GameScene()
{
	delete snakehead;
}

void GameScene::start()
{

	Scene::start();
	// Initialize any scene logic here
	FoodEaten = SoundManager::loadSound("sound/PowerTime.ogg"); 
	initFonts();
}

void GameScene::draw()
{
	Scene::draw();  

	SDL_RenderPresent(app.renderer);
	drawText(215, 20, 255, 255, 255, TEXT_RIGHT, "POINTS: %03d", points);

	if (snakehead->getIsAlive() == false)
	{
			drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 0, 0, TEXT_CENTER, "GAME OVER!");
	}
}

void GameScene::update()
{

	Scene::update();
	for (int i = 0; i < objects.size(); i++)
	{
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
				std::cout << "Food should be ded" << std::endl;
				points = points + 1 * 2;  
				DespawnFood(BodyGrow);  
				SpawnFood();
				break;
				
			}
		}
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

