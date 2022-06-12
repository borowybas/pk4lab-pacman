#include "Point.h"

Point::Point(std::string s, float a, float b, bool c)
{
    if (setUpSprite(s)) {
        pos = sf::Vector2f(a, b);
        tile_sprite.setPosition(pos);
        isPassable = c;
        this->isFood = true;
        this->eaten = false;
    }
}

bool Point::setUpSprite(std::string textureName)
{
    if (tile_texture.loadFromFile(textureName)) {
        tile_sprite.setTexture(tile_texture);
    }
}

