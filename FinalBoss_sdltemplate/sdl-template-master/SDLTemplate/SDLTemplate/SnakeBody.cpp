#include "SnakeBody.h"
SnakeBody::SnakeBody(int startX, int startY)
{
    x = startX;
    y = startY;
    prevX = x;
    prevY = y;
}

void SnakeBody::start()
{
    width = CELL_SIZE;
    height = CELL_SIZE;

    //movement timer for tile-based feel
    BodyMoveTimer = 20;
    BodyCurrMoveTimer = BodyMoveTimer; 
 
}

void SnakeBody::update() {
    prevX = x;
    prevY = y;

    if (BodyCurrMoveTimer > 0)
        BodyCurrMoveTimer--;

    if (BodyCurrMoveTimer == 0)
    {
        if (headTarget)
        {
            x = headTarget->getPrevX();
            y = headTarget->getPrevY();
        }
        else if (followTarget)
        {
            x = followTarget->getPrevX();
            y = followTarget->getPrevY();
        }

        BodyCurrMoveTimer = BodyMoveTimer;   // ← RESET TIMER
    }


}

void SnakeBody::draw() {
    SDL_Rect rect = { x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE };

    if (followTarget == nullptr && headTarget != nullptr) {
        // First segment (follows head)
        SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 255); // green
    }
    else {
        // Other segments
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 255, 255); // blue
    }

    SDL_RenderFillRect(app.renderer, &rect);
} 
void SnakeBody::setFollowTarget(SnakeBody* target) {
    followTarget = target;
}

void SnakeBody::setHeadTarget(SnakeHead* head) {
    headTarget = head;
}