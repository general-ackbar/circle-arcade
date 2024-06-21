#include "Laser.h"

//#define HEIGHT 768 // $480

Laser::Laser(Vector2D position, int speed, int verticalHeight)
{
    this->position = position;
    this->speed = speed;
    this->screenHeight = verticalHeight;
    active = true;
//    debugText = CString("Update called: ");
}

void Laser::Draw(C2DGraphics *graphics) {
    
//    debugText.Format("Laser is %s and has position: {%f, %f}", (active ? "ACTIVE" : "INACTIVE"), position.x, position.y);
//    graphics->DrawText(10,200, WHITE_COLOR, debugText);

    if(active)
    {
        graphics->DrawRect(position.x, position.y, 4, 15, COLOR16(29, 26, 7));

    }
}

Rectangle Laser::GetRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}

void Laser::Update() {    
    if(active) {

        position.y += speed;
        if(position.y > screenHeight - 10 || position.y < 10) {
            active = false;
        }
    }
}