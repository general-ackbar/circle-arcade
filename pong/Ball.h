#pragma once

#include <circle/2dgraphics.h>
#include <circle/bcmrandom.h>
#include "Court.h"

class Ball {
 public:    
    Ball(int radius = 10);
    void Draw(C2DGraphics *graphics);
    void Move();
    void ResetBall();
    void FlipHorisontalDirection();
    void FlipVerticalDirection();
    void setPosition(int x, int y);
    void setSpeed(int x_speed, int y_speed);
    void setCourt(Court *c);
    int getX() {return x;};
    int getY() {return y;};
    int getRadius() {return radius;};


private:
    float x, y;
    int speed_x, speed_y;
    int radius;
    Court *court;
    CBcmRandomNumberGenerator rnd = CBcmRandomNumberGenerator();

};