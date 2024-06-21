#pragma once
#include "Snake.h"
#include "Food.h"
#include "../Game.h"
#include "../utils/Image.h"
#include "../utils/Number.h"
#include "../utils/Sound.h"
#include "../utils/FontWriter.h"
#include <circle/2dgraphics.h>
#include <circle/usb/usbgamepad.h>
#include <circle/timer.h>

class SnakeGame : public Game
{
public: 
    SnakeGame(int width = 0, int height = 0);
    ~SnakeGame();
    void Draw(C2DGraphics *graphics) override;
    void Update(CTimer *timer) override;    
    void HandleInput(TGamePadState gamePadState) override;
    

private:
    void DrawUI(C2DGraphics *graphics);
    void CheckCollisionWithFood();
    void CheckCollisionWithEdges();
    void CheckCollisionWithTail();
    void checkForHighscore();
    void GameOver();

    Snake snake;
    Food food;

    CString debugText;
    CString highscoreText;

    bool allowMove = false;
    
    int offset; 
	int cellSize;
	int cellCount;


    int gameSpeed = 20;

    Image *imgLogo = nullptr;
    Sound *sndApple = nullptr;
    Sound *sndCrash = nullptr;
    Number number;
    FontWriter *writer = nullptr;
};