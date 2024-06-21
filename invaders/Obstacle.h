#pragma once
#include "../utils/Math.h"
#include "../utils/Array.h"
#include <circle/2dgraphics.h>
#include <circle/string.h>
#include "ObstacleBlock.h"

#define OBSTACLE_WIDTH 23
#define OBSTACLE_HEIGHT 13

class Obstacle {
    public:
        Obstacle(){};
        Obstacle(Vector2D position);
        void Draw(C2DGraphics *graphics);
        Rectangle GetRect();
        Vector2D position;
        Array<ObstacleBlock> blocks = Array<ObstacleBlock>();
        static int grid[OBSTACLE_HEIGHT][OBSTACLE_WIDTH];
    private:
        CString debugText;
};