#pragma once
#include <SFML/Graphics.hpp>
#include "Gametile.h"
#include <string>
#ifndef POINT_H
#define POINT_H

class Point : public GameTile{
public:
	
	Point(std::string s, float a, float b, bool c);
	//Point();
	virtual bool setUpSprite(std::string);

	//const sf::Sprite& getSprite() const;//moze tu polimorfizm z pacmanem??
};

#endif