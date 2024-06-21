#include "Cpu.h"

Cpu::Cpu() : Paddle()
{
    delay = 0;
}

void Cpu::SetDelay(int delay)
{
    this->delay = delay;
}

void Cpu::Update(int ball_y)
{
    if(delay > 0)
        delay--;
    
    if(delay > 0)
        return;

    if (y + height / 2 > ball_y)
    {
        y = y - speed;
    }
    if (y + height / 2 <= ball_y)
    {
        y = y + speed;
    }
    LimitMovement();
}
