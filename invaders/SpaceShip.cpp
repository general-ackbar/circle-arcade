#include "SpaceShip.h"

#define OFFSET_Y 20


Spaceship::Spaceship(Rectangle screen)
{
    image = new Image("/gfx/invaders/spaceship.lmi");
    screenWidth = screen.width;
    screenHeight = screen.height;

    position.x = (screenWidth - image->getWidth())/2;
    position.y = screenHeight - image->getHeight() - OFFSET_Y;
    lastFireTime = 0.0;    
    lasers = Array<Laser*>();
    speed = 7;
    laserSpeed = -6;

}

Spaceship::~Spaceship() {
    delete image;
}

void Spaceship::Draw(C2DGraphics *graphics) {
    image->DrawAt(position.x, position.y, graphics);

    //debugText.Format("Screen: %ix%i and position: {%.0f, %.0f}, lasers: %i", screenWidth, screenHeight, position.x, position.y, lasers.getSize());
    //graphics->DrawText(10, 100, WHITE_COLOR, debugText );
}

void Spaceship::MoveLeft() {
    position.x -= speed;
    if(position.x < image->getWidth()/2) {
        position.x = image->getWidth()/2;
    }
}

void Spaceship::MoveRight() {
    position.x += speed;
    if(position.x > screenWidth - image->getWidth() - image->getWidth()/2) {
        position.x = screenWidth - image->getWidth() - image->getWidth()/2;
    }
}

bool Spaceship::FireLaser(float ticks)
{
    if(ticks - lastFireTime >= 35) {
        
        lasers.push_back(new Laser({position.x + image->getWidth()/2 - 2,position.y}, laserSpeed, screenHeight));
        
        lastFireTime = ticks;
        return true;
    }
    return false;
}

Rectangle Spaceship::GetRect()
{
    return {position.x, position.y, float(image->getWidth()), float(image->getHeight())};
}


void Spaceship::Reset()
{
    position.x = (screenWidth - image->getWidth())/ 2.0f;
    position.y = screenHeight - image->getHeight() - OFFSET_Y;
    
    lasers.clear();

}
