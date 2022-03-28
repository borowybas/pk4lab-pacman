#include "gameTile.h"

GameTile::GameTile(std::string textureName, float x, float y, bool passable) {
    if (setUpSprite(textureName)) {
        pos = sf::Vector2f(x, y);
        tile_sprite.setPosition(pos);
        isPassable = passable;
    }
        
}

bool GameTile::setUpSprite(std::string textureName) {
  //textureName = "C:\\Users\\Admin\\Pictures\\tile.png"
    if (tile_texture.loadFromFile(textureName)) {
        tile_sprite.setTexture(tile_texture);
    }
    //sf::Sprite spacman_sprite;


}