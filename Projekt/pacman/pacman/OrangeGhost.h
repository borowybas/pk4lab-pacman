#pragma once
#include <SFML/Graphics.hpp>
#include "Ghost.h"
#include <string>
#ifndef ORANGEGHOST_H
#define ORANGEGHOST_H
class OrangeGhost : public Ghost {
public:
	OrangeGhost();
	~OrangeGhost() {};
	virtual void loadTexture();
	virtual void setUpMoveVector();
};

#endif