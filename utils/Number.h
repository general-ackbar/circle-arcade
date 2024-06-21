
#ifndef Number_h
#define Number_h
#pragma once

#include "Image.h"

class Number{


    
private:
    Image digits[10] {
        Image("/gfx/digits/0.lmi"),
        Image("/gfx/digits/1.lmi"),
        Image("/gfx/digits/2.lmi"),
        Image("/gfx/digits/3.lmi"),
        Image("/gfx/digits/4.lmi"),
        Image("/gfx/digits/5.lmi"),
        Image("/gfx/digits/6.lmi"),
        Image("/gfx/digits/7.lmi"),
        Image("/gfx/digits/8.lmi"),
        Image("/gfx/digits/9.lmi")
    }; 

public:	
    ~Number();
    Number();  
    void Draw(int x, int y, int number, C2DGraphics *graphics, ImageAlignment align = TopLeft);
};

#endif 
