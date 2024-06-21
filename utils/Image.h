//
//  LMI
//
//  Created by Jonatan Yde on 06/12/2017.
//  Copyright © 2017 Codeninja. All rights reserved.
//



#ifndef Image_h
#define Image_h
#pragma once

#include <fatfs/ff.h>
#include <circle/util.h>
#include <circle/alloc.h>
#include <circle/2dgraphics.h>
#define bytes_to_u16(MSB,LSB) (((unsigned int) ((unsigned char) MSB)) & 255)<<8 | (((unsigned char) LSB)&255)

enum ImageAlignment
{
    TopLeft,
    CenterLeft,
    BottomLeft,
    Center,
    TopCenter,
    TopRight
};

class Image{

    
private:
    uint16_t* data;    
    unsigned int bitsPerPixel;
    unsigned int height;
    unsigned int width;
    unsigned int headerSize;

    bool copy;

    void DrawTinted(C2DGraphics *gfx,  unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, unsigned nSourceX, unsigned nSourceY, unsigned nSourceWidth, unsigned nSourceHeight, TScreenColor *PixelBuffer, TScreenColor TransparentColor, TScreenColor tint);

public:
	Image();
    ~Image();
    Image(const char* filename);  
    Image(const Image& other);    
    Image& operator=(const Image&) = delete;
    void DrawAt(int x, int y, C2DGraphics *graphics, ImageAlignment align = TopLeft, TScreenColor transparency = 0xff, TScreenColor tint = 0x00);     
    uint16_t* getImageData16();
    int getWidth();
    int getHeight();
    int getBitsPerColor();
};

#endif 
