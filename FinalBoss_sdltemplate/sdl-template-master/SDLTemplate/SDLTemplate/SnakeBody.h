#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h"
#include "SoundManager.h"
#include <vector>
#include "SnakeHead.h"
class SnakeHead;  // forward declaration
class SnakeBody: public GameObject
{
public:
    SnakeBody(int startX, int startY);
    void start() override;
    void update() override; // follow the target
    void draw() override;   // render segment

    void setFollowTarget(SnakeBody* target); // follow another segment
    void setHeadTarget(SnakeHead* head);     // first segment follows head
    void setPrevPosition(int px, int py) { prevX = px; prevY = py; }
    int getX() { return x; }
    int getY() { return y; }
    int getWidth() { return width; }
    int getHeight() { return height; }
    int getPrevX() { return prevX; }
    int getPrevY() { return prevY; }

private:
    int x, y;       // current position
    int prevX, prevY; // previous position
    float BodyMoveTimer;
    float BodyCurrMoveTimer;

    int width, height; 
    bool hasMoved; 
    SnakeBody* followTarget = nullptr;
    SnakeHead* headTarget = nullptr;

    SDL_Texture* texture;
};
