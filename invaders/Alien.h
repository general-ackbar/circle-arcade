#pragma once
#include "../utils/Math.h"
#include "../utils/Image.h"
#include <circle/2dgraphics.h>


class Alien {
    public:        
        Alien(int type=1, Vector2D position = {0,0});
        ~Alien();
        void Update(int direction);
        void Draw(C2DGraphics *graphics);
        int GetType() { return type; };
        Rectangle GetRect();
        Vector2D position;
    
    private:
        int type;
        Image *texture; 
        //static Image* alienImages[3];   
};