#pragma once
#include "../utils/Math.h"
#include "../utils/Image.h"
#include <circle/2dgraphics.h>
#include <circle/bcmrandom.h>

class MysteryShip {
    public:
        MysteryShip(Rectangle screen = {0,0,0,0});
        ~MysteryShip();
        void Update();
        void Draw(C2DGraphics *graphics);
        void Spawn(int yOffset);
        Rectangle getRect();
        int GetHeight() { return image->getHeight(); }
        bool alive;
    private:
        Vector2D position;
        Image *image;
        int speed;
        int screenWidth;
        int screenHeight;
        CBcmRandomNumberGenerator rnd = CBcmRandomNumberGenerator();
};