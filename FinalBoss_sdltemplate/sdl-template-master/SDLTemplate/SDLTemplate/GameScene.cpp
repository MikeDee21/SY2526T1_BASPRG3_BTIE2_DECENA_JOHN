#include "GameScene.h"

GameScene::GameScene()
{
	snakehead = new SnakeHead();
	snakehead->start();
	addGameObject(snakehead);

	// OPTIONAL: Start with ONE body segment
	//SnakeBody* first = new SnakeBody(snakehead->getPositionX() - 1, snakehead->getPositionY());
	//first->setHeadTarget(snakehead);
	//first->setPrevPosition(first->getX(), first->getY());
	//first->start();
	//addGameObject(first);


	addSegment(); 
	points = 0;
	SpawnFood();
}

GameScene::~GameScene()
{
	delete snakehead;
}

void GameScene::start()
{
	Scene::start();
	FoodEaten = SoundManager::loadSound("sound/PowerTime.ogg");
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

	if (!snakehead->getIsAlive())
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 0, 0, TEXT_CENTER, "GAME OVER!");
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
				addSegment();
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

// --- Add a new segment ---
void GameScene::addSegment()
{
	std::cout << "There should be one more segment" << std::endl; 
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

