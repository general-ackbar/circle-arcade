#pragma once
#include "../Game.h"
#include "Ball.h"
#include "Cpu.h"
#include "Paddle.h"
#include "Court.h"
#include "../utils/Sound.h"
#include <circle/2dgraphics.h>
#include <circle/usb/usbgamepad.h>
#include <circle/timer.h>

class PongGame : public Game
{
public:
    
    PongGame(int width = 0, int height = 0);
    ~PongGame();
    void Draw(C2DGraphics *graphics) override;
    void Update(CTimer *timer) override;
    void HandleInput(TGamePadState gamePadState) override;
    


private:
    void DrawUI(C2DGraphics *graphics);
    
    Ball ball;
    Paddle player;
    Cpu cpu;
    Court court;
    Number number;

    

    Sound *sndPaddle = nullptr;
        

};