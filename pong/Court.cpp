#include "Court.h"
#define WHITE COLOR16(31,31,31)


Court::Court(int originX, int originY, int width, int height)
{
    this->x = originX;
    this->y = originY;
    this->width = width;
    this->height = height;
    center = {this->x + (this->width/2), this->y + (this->height/2)};
}

Court::~Court()
{

}

void Court::IncreaseLeftScore(){
    leftScore = leftScore + 1;
}

void Court::IncreaseRightScore(){
    rightScore = rightScore + 1;
}

void Court::ResetScore(){
    rightScore = 0;
    leftScore = 0;
}

void Court::Draw(C2DGraphics *graphics)
{
    graphics->ClearScreen(COLOR16(0,29,0 ));
    
    graphics->DrawRectOutline(x, y, width-1, height-1, WHITE);
    graphics->DrawRectOutline(x+1, y+1, width-2, height-2, WHITE);
    graphics->DrawRectOutline(x+2, y+2, width-4, height-4, WHITE);
    graphics->DrawRectOutline(x+3, y+3, width-6, height-6, WHITE);

    graphics->DrawCircleOutline(center.x, center.y, 149, WHITE);
    graphics->DrawCircleOutline(center.x, center.y, 150, WHITE);
    graphics->DrawCircleOutline(center.x, center.y, 151, WHITE);
    
    graphics->DrawLine(center.x-1, y+1, center.x -1, y + height-1, WHITE);
    graphics->DrawLine(center.x,   y+1, center.x  , y + height-1, WHITE);
    graphics->DrawLine(center.x+1, y+1, center.x +1, y + height-1, WHITE);
}
