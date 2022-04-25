#pragma once
#include <SFML/Graphics.hpp>


#ifndef PACMAN_H
#define PACMAN_H

class Pacman{
public:
	enum Direction_e {
		LEFT = 1,
		RIGHT,
		UP,
		DOWN,
	};
	Direction_e spriteDirection;

	float speed = 5;
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Sprite pacman_sprite;
	sf::Texture pacman_texture;
	//int direction;
	int spriteAngle;
	void setDirection();
	float currentRotation;
	Pacman();
	~Pacman();
	//void initPacman();
	void setRotation();
	void update();
	void updateInput();//strzealki
	void movePlayer();
	void render(sf::RenderTarget* target);

	float xVelocity = 3;
	float yVelocity = 3;
};

#endif