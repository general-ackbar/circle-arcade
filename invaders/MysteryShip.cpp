#include "MysteryShip.h"

MysteryShip::MysteryShip(Rectangle screen)
{
    image = new Image("/gfx/invaders/mystery.lmi");
    alive = false;
    screenWidth = screen.width;
    screenHeight = screen.height;
}

MysteryShip::~MysteryShip() {
    delete image;
}

void MysteryShip::Spawn(int yOffset) {
    position.y = yOffset;
    int side = rnd.GetNumber() % 2;

    if(side == 0) {
        position.x = 25;
        speed = 3;
    } else {
        position.x = screenWidth - image->getWidth() - 25;
        speed = -3;
    }
    alive = true;
}


Rectangle MysteryShip::getRect()
{
    if(alive){
        return {position.x, position.y, float(image->getWidth()), float(image->getHeight())};
    } else {
        return {position.x, position.y, 0, 0};
    }
}

void MysteryShip::Update() {
    if(alive) {
        position.x += speed;
        if(position.x > screenWidth - image->getWidth() -25 || position.x < 25) {
            alive = false;
        }
    }
}

void MysteryShip::Draw(C2DGraphics *graphics) {
    if(alive) {
        image->DrawAt(position.x, position.y, graphics, TopLeft, 0x00);
    }
}