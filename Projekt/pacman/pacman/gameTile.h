#pragma once
#include <SFML/Graphics.hpp>

#ifndef GAMETILE_H
#define GAMETILE_H

class GameTile {
public:
	bool isPassable;
	sf::Vector2f pos;
	sf::Texture tile_texture;
	sf::Sprite tile_sprite;
	GameTile(std::string, float, float, bool);
	bool setUpSprite(std::string);

};

#endif