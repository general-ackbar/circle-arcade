#include "Alien.h"

//Image* Alien::alienImages[3] = {};

Alien::Alien(int type, Vector2D position)
{
    this->type = type;
    this->position = position;

    switch (type) {
        case 1:
            texture = new Image("/gfx/invaders/alien_1.lmi");
            break;
        case 2:
            texture = new Image("/gfx/invaders/alien_2.lmi");
            break;
        case 3: 
            texture = new Image("/gfx/invaders/alien_3.lmi");
            break;
        default:
            texture = new Image("/gfx/invaders/alien_1.lmi");
            break;
    }
}

Alien::~Alien()
{
    delete texture;
}

void Alien::Draw(C2DGraphics *graphics) {
    texture->DrawAt(position.x, position.y, graphics);
}


Rectangle Alien::GetRect()
{
    return {
        position.x, 
        position.y,
        float(texture->getWidth()),
        float(texture->getHeight())
    };
}

void Alien::Update(int direction) {
    position.x += direction;
}
