#pragma once
#include <SFML/Graphics.hpp>


#ifndef GAMETILE_H
#define GAMETILE_H

class GameTile {
public:
	bool isPassable;
	bool isFood;
	bool eaten;
	sf::Vector2f pos;
	sf::Texture tile_texture;
	sf::Sprite tile_sprite;
	GameTile(std::string, float, float, bool);
	GameTile() {};
	virtual bool setUpSprite(std::string);

	const sf::Sprite& getSprite() const;//moze tu polimorfizm z pacmanem??
};

#endif