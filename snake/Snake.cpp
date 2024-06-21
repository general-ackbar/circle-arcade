#include "Snake.h"


Snake::Snake(int size) {
        cellSize = size;
        offset = cellSize *2;
        body.push_front(Vector2D{6, 9});
        body.push_front(Vector2D{5, 9});
        body.push_front(Vector2D{4, 9});
    }

void Snake::Draw(C2DGraphics *graphics) {        
        for (int i = 0; i < body.count(); i++)
        {            
            float x = body.peek(i).x;
            float y = body.peek(i).y;
            graphics->DrawRect(offset + x * cellSize, offset + y * cellSize, cellSize, cellSize, COLOR16(31,31,0));
        }
    }


void Snake::Update()
    {
        Vector2D nextPosition = Math::Vector2DAdd(body.peek_front(), direction);
        body.push_front(nextPosition);
        if (addSegment == true)
        {
            addSegment = false;            
        }
        else
        {
            body.pop_end();
        }
    }

void Snake::Reset()
    {   
        body.clear();
        body.push_front(Vector2D{6, 9});
        body.push_front(Vector2D{5, 9});
        body.push_front(Vector2D{4, 9});
        
        direction = {1, 0};
    }

