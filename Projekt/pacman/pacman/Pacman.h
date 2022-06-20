#pragma once
#include <SFML/Graphics.hpp>
#include <semaphore>
#ifndef PACMAN_H
#define PACMAN_H

class Pacman{

	enum Direction_e {
		LEFT = 1, RIGHT, UP, DOWN,
	};
	Direction_e spriteDirection;

	sf::Sprite pacman_sprite;
	sf::Vector2f position;
	sf::Texture pacman_texture;
	int spriteAngle;

	sf::RectangleShape leftTunnel;
	sf::RectangleShape rightTunnel;
	bool tunnelCollision;
	bool tunnelInUsage;

public:
	float xVelocity = 3;
	float yVelocity = 3;
	bool isAlive;
	sf::RectangleShape pacmanCollision;

	Pacman();
	~Pacman();

	void setDirection();
	void update();
	void updateInput();//strzalki
	void movePlayer();
	void render(sf::RenderTarget* target);
	bool useTunnel(sf::RectangleShape& rectA, sf::RectangleShape& rectB);
	void useRightTunnel();
	void useLeftTunnel();
};

#endif