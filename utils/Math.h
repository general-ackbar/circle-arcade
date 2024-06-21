
#pragma once
#ifndef MATH_H
#define MATH_H



#define EPSILON 0.000001f

typedef struct Rectangle
{
    float x;
    float y;
    float width;
    float height;
} Rectangle;

typedef struct Point{
    int x;
    int y;
} Point;

typedef struct Size{
    int width;
    int heigt;
} Size;

typedef struct Vector2D {
    float x;                // Vector x component
    float y;                // Vector y component
} Vector2D;

class Math
{

private:


public:
    Math();
    ~Math();

    static int Vector2DEquals(Vector2D p, Vector2D q);
    static Vector2D Vector2DAdd(Vector2D v1, Vector2D v2);
    static bool CheckRectangleCollision(Rectangle rec1, Rectangle rec2);
    static int isnan(float x);
    static float fmaxf(float x, float y);
    static float fabsf(float x);
};






#endif  