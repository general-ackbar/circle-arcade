#include "Food.h"


Food::Food(int size, int gridsize) {
    cellCount = gridsize;
    cellSize = size;
    offset = cellSize *2;
}

Food::~Food() {

}

void Food::Draw(C2DGraphics *graphics) {
        graphics->DrawRect(offset + position.x * cellSize, offset + position.y * cellSize, cellSize, cellSize,  COLOR16(31,0,0));
    }

Vector2D Food::GenerateRandomCell()
    {
        float x = rnd.GetNumber() % (cellCount -1);
        float y = rnd.GetNumber() % (cellCount -1);
        return Vector2D{x, y};
    }

void Food::SetRandomPos(Deque snakeBody)
    {
        Vector2D newPosition = GenerateRandomCell();
        while (snakeBody.Contains(newPosition)) {
            newPosition = GenerateRandomCell();
        }
        this->position = newPosition;
    }