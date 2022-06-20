#include "Ghost.h"

Ghost::Ghost(int posX, int posY)
{
	this->position.x = posX;
	this->position.y = posY;
	this->ghost_sprite.setPosition(position);
	this->ghost_sprite.setOrigin(20, 20);
	
	this->ghostCollision.setPosition(position);
	this->ghostCollision.setOrigin(20, 20);
	this->ghostCollision.setSize(sf::Vector2f(40, 40));
}

void Ghost::moveGhost(std::vector<sf::Vector2f>& moveVector)
{
	bool flag=0;
	for (int i = 0; flag == 0; i++) {
		
		if (moveVector[i].x > 0) { //prawo
			this->position.x += 1;
			this->ghost_sprite.setPosition(this->position);
			moveVector[i].x -= 1;
			flag = 1;
		}
		else if (moveVector[i].x < 0) { //lewo
			this->position.x -= 1;
			this->ghost_sprite.setPosition(this->position);
			moveVector[i].x += 1;
			flag = 1;
		}
		else if(moveVector[i].y > 0) { //dó³
			this->position.y += 1;
			this->ghost_sprite.setPosition(this->position);
			moveVector[i].y -= 1;
			flag = 1;
		}
		else if (moveVector[i].y < 0) { //góra
			this->position.y -= 1;
			this->ghost_sprite.setPosition(this->position);
			moveVector[i].y += 1;
			flag = 1;
		}
		if (i == moveVector.size()) {
			this->setUpMoveVector();
		}
	}
}

void Ghost::updateGhost()
{
	this->moveGhost(this->moveVector);
	ghostCollision.setPosition(this->position);
}

void Ghost::render(sf::RenderTarget* target)
{
	target->draw(this->ghost_sprite);
}
