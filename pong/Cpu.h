#pragma once

#include "Paddle.h"

class Cpu : public Paddle {
 
 public:
    Cpu();
    void SetDelay(int delay);
    void Update(int ball_y);

private:
    int delay;
};