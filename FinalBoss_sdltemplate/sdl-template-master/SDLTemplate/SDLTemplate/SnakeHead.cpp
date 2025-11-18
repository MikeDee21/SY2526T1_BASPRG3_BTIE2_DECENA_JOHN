#include "SnakeHead.h"
#include "SnakeFood.h"
void SnakeHead::start()
{
	texture = loadTexture("gfx/SnakeHead.jpg");

    // Start in the middle of the grid
    x = GRID_COLUMNS / 2;
    y = GRID_ROWS / 2;

    // Sprite dimensions (pixels)
    width = 50;
    height = 50;

    // IMPORTANT: initialize previous position
    prevX = x;
    prevY = y;

    //Constantly moving & moves right by default 

    dirX = 1;
    dirY = 0;

    //movement timer for tile-based feel
    MoveTimer = 18;
    CurrMoveTimer = 0;

    //snake state
    isAlive = true; 
  
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    DeadSound = SoundManager::loadSound("sound/Fahh.ogg");
}




void SnakeHead::update()
{
   
    // Decrement movement cooldown each frame
    if (CurrMoveTimer > 0)
        CurrMoveTimer--;

    // Handle direction input (don’t move yet)
    if (!isAlive) return;
    {
        if (app.keyboard[SDL_SCANCODE_W] && dirY == 0)
        {
            dirX = 0;
            dirY = -1;
        }
        else if (app.keyboard[SDL_SCANCODE_S] && dirY == 0)
        {
            dirX = 0;
            dirY = 1;
        }
        else if (app.keyboard[SDL_SCANCODE_A] && dirX == 0)
        {
            dirX = -1;
            dirY = 0;
        }
        else if (app.keyboard[SDL_SCANCODE_D] && dirX == 0)
        {
            dirX = 1;
            dirY = 0;
        }

        // Move only when timer hits 0
        if (CurrMoveTimer == 0)
        {
            //get previous x & y 

            prevX = x;
            prevY = y;

            x += dirX;
            y += dirY;

            CurrMoveTimer = MoveTimer;  // Reset cooldown
            if (x < 0 || x >= GRID_COLUMNS || y < 0 || y >= GRID_ROWS)
            {
                // Snake hit the border → player dies
                isAlive = false;    
                SoundManager::playSound(DeadSound);

                std::cout << "you ded" << std::endl; 
               
            }
        }
    }
}

void SnakeHead::draw() 
{
  
    SDL_Rect dest;
    dest.x = x * CELL_SIZE + (CELL_SIZE - width) / 2;
    dest.y = y * CELL_SIZE + (CELL_SIZE - height) / 2;
    dest.w = width;
    dest.h = height;

    SDL_RenderCopy(app.renderer, texture, NULL, &dest); 
}

bool SnakeHead::getIsAlive()
{
    return isAlive; 
}

void SnakeHead::KillSnake()
{
    isAlive = false; 
}



int SnakeHead::getPositionX()
{
    return x;
}

int SnakeHead::getPositionY()
{
    return y;
}

int SnakeHead::getWidth()
{
    return width;
}

int SnakeHead::getHeight() 
{
    return height;
}

int SnakeHead::getPrevX()
{
    return prevX;
}

int SnakeHead::getPrevY()
{
    return prevY; 
}
