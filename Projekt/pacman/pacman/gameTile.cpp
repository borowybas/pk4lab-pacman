#include "gameTile.h"

GameTile::GameTile(std::string textureName, int x, int y) {
    if (setUpSprite(textureName)) {
        pos = sf::Vector2f(x, y);
        tile_sprite.setPosition(pos);
        this->isFood = false;
        this->eaten = false;
    }
}

bool GameTile::setUpSprite(std::string textureName) {
  
    if (tile_texture.loadFromFile(textureName)) {
        tile_sprite.setTexture(tile_texture);
        return true;
    }
    return false;
}
