#pragma once
#include <SFML/Graphics.hpp>

#ifndef PACMAN_H
#define PACMAN_H

class Pacman{
public:
	enum Direction_e {
		LEFT = 1, RIGHT, UP, DOWN,
	};
	Direction_e spriteDirection;

	sf::Vector2f position;
	sf::Sprite pacman_sprite;
	sf::RectangleShape pacmanCollision;
	sf::Texture pacman_texture;
	int spriteAngle;
	void setDirection();
	Pacman();
	~Pacman();

	const sf::Sprite& getSprite() const;

	void update();
	void updateInput();//strzalki
	void movePlayer();
	void render(sf::RenderTarget* target);
	sf::RectangleShape leftTunnel;
	sf::RectangleShape rightTunnel;
	bool useTunnel(sf::RectangleShape& rectA, sf::RectangleShape& rectB);
	void useLeftTunnel();
	void useRightTunnel();
	bool tunnelCollision;
	bool tunnelInUsage;
	float xVelocity = 3;
	float yVelocity = 3;
	bool isAlive;
};

#endif