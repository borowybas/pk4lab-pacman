#include "Pacman.h"
#include <iostream>
#include <thread>
#include <semaphore>
#include <barrier>
#include <chrono>
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
		this->pacman_sprite.scale(0.875, 0.875);
		this->spriteAngle = 0;
		sf::Vector2f pacmanSize; pacmanSize.x = 35; pacmanSize.y = 35;
		this->pacmanCollision.setSize(pacmanSize);
		//this->pacmanCollision.setOrigin(-20, -20);
		sf::Vector2f size;
		size.x = 0; size.y = 40;
		this->leftTunnel.setSize(size);
		this->rightTunnel.setSize(size);
		this->rightTunnel.setPosition(780+40, 380);
		this->leftTunnel.setPosition(-20-40, 380);
		this->tunnelCollision = 0;
		this->tunnelInUsage = 0;
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
	//std::cout << this->xVelocity<<" ";
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
std::counting_semaphore semaphore1(0);
std::counting_semaphore semaphore2(0);

void Pacman::useRightTunnel() {//1
	semaphore1.acquire();
	if (/*this->tunnelCollision == 0 &&*/ useTunnel(this->pacmanCollision, this->rightTunnel)) {
		this->tunnelInUsage = 1;
		this->position.x = leftTunnel.getPosition().x+40;
		this->position.y = leftTunnel.getPosition().y;
		this->pacman_sprite.setPosition(position);
		std::cout << pacman_sprite.getPosition().x << " " << pacman_sprite.getPosition().y << std::endl;
		//Sleep(0);
		//std::this_thread::sleep_for(std::chrono::seconds(5));
		this->tunnelInUsage = 0;
	}
	
	semaphore2.release();
}

void Pacman::useLeftTunnel() {//2
	semaphore1.release();
	semaphore2.acquire();
	if (/*this->tunnelCollision == 0 &&*/ useTunnel(this->pacmanCollision, this->leftTunnel)) {
		this->tunnelInUsage = 1;
		this->position.x = rightTunnel.getPosition().x-40;
		this->position.y = rightTunnel.getPosition().y;
		this->pacman_sprite.setPosition(position);
		std::cout << pacman_sprite.getPosition().x << " " << pacman_sprite.getPosition().y << std::endl;
		//std::this_thread::sleep_for(std::chrono::seconds(5));
		this->tunnelInUsage = 0;
	}
	//sleep
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	//semaphore.release();
}

void Pacman::movePlayer()
{
		this->pacman_sprite.setPosition(position);
		//this->useTunnel(this->pacmanCollision, this->leftTunnel);
		//if (this->useTunnel(this->pacmanCollision, this->leftTunnel)) {
		//	this->leftTunnelCollision = 1;
		//	this->rightTunnelCollision = 0;
		//}
		//else if (this->useTunnel(this->pacmanCollision, this->rightTunnel)) {
		//	this->leftTunnelCollision = 0;
		//	this->rightTunnelCollision = 1;
		//}
		//else {
		//	this->leftTunnelCollision = 0;
		//	this->rightTunnelCollision = 0;
		//}
		
			std::thread thread1(&Pacman::useLeftTunnel, this);
			std::thread thread2(&Pacman::useRightTunnel, this);

			thread1.join(); thread2.join();
			
		
		//sf::RectangleShape tempShape;
		
		//void useLeftTunnel() {
		//	if (useTunnel(this->pacmanCollision, this->rightTunnel)) {

		//		this->position.x = leftTunnel.getPosition().x;
		//		this->position.y = leftTunnel.getPosition().y;
		//		this->pacman_sprite.setPosition(position);
		//		std::cout << pacman_sprite.getPosition().x << " " << pacman_sprite.getPosition().y << std::endl;
		//		//Sleep(0);
		//	}
		//};

		/*if (useTunnel(this->pacmanCollision, this->leftTunnel)) {
			this->position.x = rightTunnel.getPosition().x;
			this->position.y = rightTunnel.getPosition().y;
			this->pacman_sprite.setPosition(position);
			std::cout << pacman_sprite.getPosition().x << " " << pacman_sprite.getPosition().y << std::endl;
		}*/
		//przechodzenie przez ekran
		//2*use tunnel
		
}

void Pacman::render(sf::RenderTarget* target)
{
	target->draw(this->pacman_sprite);
}

bool Pacman::useTunnel(sf::RectangleShape& rectA, sf::RectangleShape& rectB)
{
	if (/*this->tunnelInUsage == 0 && */this->tunnelCollision == 0 && rectA.getPosition().x + rectA.getSize().x >= rectB.getPosition().x && //->
		rectB.getPosition().x + rectB.getSize().x >= rectA.getPosition().x && //<-
		rectA.getPosition().y + rectA.getSize().y >= rectB.getPosition().y &&
		rectB.getPosition().y + rectB.getSize().y >= rectA.getPosition().y) {
		this->tunnelCollision = 1;
		return true;
	}
	else {
		this->tunnelCollision = 0;
		return false;
	}

}




