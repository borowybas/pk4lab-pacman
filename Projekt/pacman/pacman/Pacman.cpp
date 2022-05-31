#include "Pacman.h"
#include <iostream>
void Pacman::setDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->spriteDirection = Pacman::RIGHT;
		this->spriteAngle = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->spriteDirection = Pacman::LEFT;
		this->spriteAngle = 180;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->spriteDirection = Pacman::UP;
		this->spriteAngle = 270;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->spriteDirection = Pacman::DOWN;
		this->spriteAngle = 90;
	}

}

Pacman::Pacman()//init var, init shape, set pos
{
	
		pacman_texture.loadFromFile("C:\\Users\\Admin\\Pictures\\pacman.png");
		position.x = 60; position.y = 60; //initial position
		this->pacman_sprite.setTexture(pacman_texture);
		this->pacman_sprite.setOrigin(20, 20);
		this->pacman_sprite.setPosition(position);
		this->spriteAngle = 0;
		sf::Vector2f pacmanSize; pacmanSize.x = 38; pacmanSize.y = 38;
		this->pacmanCollision.setSize(pacmanSize);
		//this->pacmanCollision.setOrigin(-20, -20);
}

const sf::Sprite& Pacman::getSprite() const
{
	return this->pacman_sprite;
}

Pacman::~Pacman()
{

}

void Pacman::update()
{
	this->setDirection();
	this->updateInput();
	this->movePlayer();
	pacmanCollision.setPosition(this->position);
}

void Pacman::updateInput()
{
	if (
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || 
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		
		) {
		this->xVelocity = 3;

	}
	else if (
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		) {

		this->yVelocity = 3;
	}
	std::cout << this->xVelocity<<" ";
	switch (this->spriteDirection) {
	case LEFT:
		this->position.x -= this->xVelocity;
		break;
	case RIGHT:
		this->position.x += this->xVelocity;
		break;
	case UP:
		this->position.y -= this->yVelocity;
		break;
	case DOWN:
		this->position.y += this->yVelocity;
		break;
	default:
		break;
	}

	this->pacman_sprite.setRotation(this->spriteAngle);
}

void Pacman::movePlayer()
{
		this->pacman_sprite.setPosition(position);
}

void Pacman::render(sf::RenderTarget* target)
{
	target->draw(this->pacman_sprite);
}




