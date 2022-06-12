#pragma once
#include <SFML/Graphics.hpp>
#include "Gametile.h"
#include <string>
#ifndef POINT_H
#define POINT_H

class Point : public GameTile{
public:
	//bool isPassable;
	//bool eaten;
	//sf::Vector2f pos;
	//sf::Texture tile_texture;
	//sf::Sprite tile_sprite;
	Point(std::string s, float a, float b, bool c);
	//Point();
	virtual bool setUpSprite(std::string);

	//const sf::Sprite& getSprite() const;//moze tu polimorfizm z pacmanem??
};

#endif