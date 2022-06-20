#pragma once
#include <SFML/Graphics.hpp>
#include "Ghost.h"
#include <string>
#ifndef BLUEGHOST_H
#define BLUEGHOST_H
class BlueGhost : public Ghost {
public:
	BlueGhost();
	~BlueGhost() {};
	virtual void loadTexture();
	virtual void setUpMoveVector();
};

#endif