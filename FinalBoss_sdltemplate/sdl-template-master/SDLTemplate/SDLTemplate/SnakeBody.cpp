#include "SnakeBody.h"
SnakeBody::SnakeBody(int startX, int startY) {
    x = startX;
    y = startY;
    prevX = x;
    prevY = y;
}

void SnakeBody::start()
{
    width = CELL_SIZE;
    height = CELL_SIZE;
 
}

void SnakeBody::update() {
    prevX = x;
    prevY = y;

    if (firstUpdate) {
        firstUpdate = false;
        return; // skip following on the first frame
    }

    if (headTarget)
        x = headTarget->getPrevX();
    else if (followTarget)
        x = followTarget->getPrevX();

    if (headTarget)
        y = headTarget->getPrevY();
    else if (followTarget)
        y = followTarget->getPrevY();
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