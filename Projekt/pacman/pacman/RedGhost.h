#pragma once
#include <SFML/Graphics.hpp>
#include "Ghost.h"
#include <string>
#ifndef REDGHOST_H
#define REDGHOST_H
class RedGhost : public Ghost {
public:
	RedGhost();
	~RedGhost() {};
	virtual void loadTexture();
	virtual void setUpMoveVector();
};

#endif