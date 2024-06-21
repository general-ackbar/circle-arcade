#include "ObstacleBlock.h"

ObstacleBlock::ObstacleBlock(Vector2D position)
{
    this->position = position;
}

void ObstacleBlock::Draw(C2DGraphics *graphics) {
    graphics->DrawRect(position.x, position.y, 3, 3, COLOR16(29, 26, 7));
}

Rectangle ObstacleBlock::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 3;
    rect.height = 3;
    return rect;
}
