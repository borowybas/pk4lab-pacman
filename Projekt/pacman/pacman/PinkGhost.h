#pragma once
#include <SFML/Graphics.hpp>
#include "Ghost.h"
#include <string>
#ifndef PINKGHOST_H
#define PINKGHOST_H
class PinkGhost : public Ghost {
public:
	PinkGhost();
	~PinkGhost() {};
	virtual void loadTexture();
	virtual void setUpMoveVector();
};

#endif#pragma once
