#pragma once
#include <SFML/Graphics.hpp>
#include "Gametile.h"
#include <string>

#ifndef POINT_H
#define POINT_H

class Point : public GameTile{
public:

	Point(std::string s, int a, int b); //mozna poprawic
	//Point();
	~Point() {};

	virtual bool setUpSprite(std::string);
};

#endif