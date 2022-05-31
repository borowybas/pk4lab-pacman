#include "gameTile.h"

GameTile::GameTile(std::string textureName, float x, float y, bool passable) {
    if (setUpSprite(textureName)) {
        pos = sf::Vector2f(x, y);
        tile_sprite.setPosition(pos);
        isPassable = passable;
    }
        
}

bool GameTile::setUpSprite(std::string textureName) {
  
    if (tile_texture.loadFromFile(textureName)) {
        tile_sprite.setTexture(tile_texture);
    }
    
}

const sf::Sprite& GameTile::getSprite() const
{
    return this->tile_sprite;
}
