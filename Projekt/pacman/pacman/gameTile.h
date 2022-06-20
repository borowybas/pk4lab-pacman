#pragma once
#include <SFML/Graphics.hpp>

#ifndef GAMETILE_H
#define GAMETILE_H

class GameTile {
public:

	sf::Sprite tile_sprite;
	sf::Vector2f pos;
	sf::Texture tile_texture;
	bool isFood;
	bool eaten;

	GameTile(std::string, int, int);
	GameTile() {};
	~GameTile() {};

	virtual bool setUpSprite(std::string);
};

#endif