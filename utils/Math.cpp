#include "Math.h"

Math::Math(/* args */){}

Math::~Math(){}
int Math::isnan(float x) {
    return x != x;
}

float Math::fmaxf(float x, float y) {
    // Check for NaN (Not-a-Number) inputs
    if (Math::isnan(x) || Math::isnan(y)) {
        return -1;
    }
    // Compare the values and return the maximum
    return (x > y) ? x : y;
}

float Math::fabsf(float x) {
    // Check for negative input
    if (x < 0) {
        return -x; // Return the negation of x
    } else {
        return x; // Return x if it's already positive
    }
}

int Math::Vector2DEquals(Vector2D p, Vector2D q)
{
    int result = ((Math::fabsf(p.x - q.x)) <= (EPSILON*Math::fmaxf(1.0f, Math::fmaxf(Math::fabsf(p.x), Math::fabsf(q.x))))) &&
                  ((Math::fabsf(p.y - q.y)) <= (EPSILON*Math::fmaxf(1.0f, Math::fmaxf(Math::fabsf(p.y), Math::fabsf(q.y)))));

    return result;
}

Vector2D Math::Vector2DAdd(Vector2D v1, Vector2D v2)
{
        Vector2D result = { v1.x + v2.x, v1.y + v2.y };
        return result;
}

// Check collision between two rectangles
bool Math::CheckRectangleCollision(Rectangle rec1, Rectangle rec2)
{
    bool collision = false;

    if ((rec1.x < (rec2.x + rec2.width) && (rec1.x + rec1.width) > rec2.x) &&
        (rec1.y < (rec2.y + rec2.height) && (rec1.y + rec1.height) > rec2.y)) collision = true;

    return collision;
}