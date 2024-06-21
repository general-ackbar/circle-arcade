#include "Paddle.h"


Paddle::Paddle()
{
    
}

void Paddle::setCourt(Court* court)
{
    this->court = court;
}
void Paddle::LimitMovement() {
        if (y <= court->getOriginY()) {
            y = court->getOriginY();
        }
        if (y + height >= (court->getOriginY() + court->getHeight())) {
            y = (court->getOriginY() + court->getHeight()) - height;
        }
}



void Paddle::Draw(C2DGraphics *graphics)
{
    graphics->DrawRect(x, y, width, height, COLOR16(31,31,31));
}

void Paddle::MoveUp()
{
    y -= speed;
    LimitMovement();
}

void Paddle::MoveDown()
{
    y += speed;
    LimitMovement();
}

void Paddle::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Paddle::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

void Paddle::setSpeed(int speed)
{
    this->speed = speed;
}

bool Paddle::CheckCollisionWithBall(Ball ball)
{
    bool collision = false;

    float recCenterX = x + width/2.0f;
    float recCenterY = y + height/2.0f;

    float dx = Math::fabsf(ball.getX() - recCenterX);
    float dy = Math::fabsf(ball.getY() - recCenterY);

    if (dx > (width/2.0f + ball.getRadius())) { return false; }
    if (dy > (height/2.0f + ball.getRadius())) { return false; }

    if (dx <= (width/2.0f)) { return true; }
    if (dy <= (height/2.0f)) { return true; }

    float cornerDistanceSq = (dx - width/2.0f)*(dx - width/2.0f) +
                             (dy - height/2.0f)*(dy - height/2.0f);

    collision = (cornerDistanceSq <= (ball.getRadius()*ball.getRadius()));

    return collision;
}