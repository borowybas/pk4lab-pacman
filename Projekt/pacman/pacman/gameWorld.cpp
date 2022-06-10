#include "gameWorld.h"
#include <iostream>
void GameWorld::setUpInitialState() {
	pacmanPos = sf::Vector2i(0, 0);
}


void GameWorld::setUpTiles() {
	tiles.clear();
	//std::vector< GameTile*> firstRow;
	//firstRow.push_back(new GameTile("C:\\Users\\Admin\\Documents\\GitHub\\a87312ac-gr41-repo\\Projekt\\pacman\\images\\blueTile.png", 0,0,false));

	//////// y   x
	const int arr[21][19] = {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//
		{ 0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0 },//
		{ 0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,0 },//
		{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },//
		{ 0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,1,0 },//
		{ 0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0 },//6
		{ 0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0 },//
		{ 1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1 },//
		{ 0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0 },//9
		{ 1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1 },//
		{ 0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0 },//11
		{ 1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1 },//12
		{ 0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0 },//13
		{ 0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0 },//
		{ 0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,0 },//15
		{ 0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0 },//16
		{ 0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0 },//
		{ 0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0 },//
		{ 0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0 },//
		{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },//v
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	};

	for (int row = 0; row < 21; row++) {
		std::vector<GameTile* > wholeRow;
		int y = row * 40;
		for (int col = 0; col < 19; col++) {
			int x = col * 40;

			if (arr[row][col] == 0) {
				wholeRow.push_back(new GameTile("C:\\Users\\Admin\\Documents\\GitHub\\a87312ac-gr41-repo\\Projekt\\pacman\\images\\blueTile.png", x, y, false));
			}
			else if (arr[row][col] == 1) {
				wholeRow.push_back(new GameTile("C:\\Users\\Admin\\Documents\\GitHub\\a87312ac-gr41-repo\\Projekt\\pacman\\images\\blackTile.png", x, y, true));
			}

		}
		tiles.push_back(wholeRow);
	}
}

void GameWorld::drawTiles()
{
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 19; j++) {
			this->window->draw(this->tiles[i][j]->tile_sprite);
		}
	}

}

void GameWorld::initVariables() {
	this->endGame = false;
}

void GameWorld::initWindow() {
	this->videomode = sf::VideoMode(760, 840);
	this->window = new sf::RenderWindow (this->videomode, "Pac-Man", sf::Style::Close | sf::Style::Titlebar);
}

GameWorld::GameWorld() {
	this->initVariables();
	this->initWindow();

	//gridLength = 19;
	//gridHeight = 21;
	setUpInitialState();
	setUpTiles();
	drawTiles();
	this->window->setFramerateLimit(60);
	setMapColPos();
}

GameWorld::~GameWorld() {
	delete this->window;
}

void GameWorld::pollEvents()
{
	while (this->window->pollEvent(this->myEvent)) {
		if (this->myEvent.type == sf::Event::Closed) {
			this->window->close();
		}
	}
}



void GameWorld::setMapColPos()
{
	mapColEl1.setPosition(380, 60); //360+20
	sf::Vector2f size1;
	size1.x = 40; size1.y = 80;
	mapColEl1.setSize(size1);

}

void GameWorld::updateCollision(const sf::RectangleShape& rectA, const sf::RectangleShape& rectB)
{
	if ( this->pacman.xVelocity != 0 && 
		rectA.getPosition().x + rectA.getSize().x + 3 >= rectB.getPosition().x && //->
		rectB.getPosition().x + rectB.getSize().x >= rectA.getPosition().x -3 && //<-
		rectA.getPosition().y + rectA.getSize().y -3 >= rectB.getPosition().y &&
		rectB.getPosition().y + rectB.getSize().y >= rectA.getPosition().y +3
		
		) {
		this->pacman.xVelocity = 0;

		
		//std::cout << "collision x";
	}
	else
		if (this->pacman.yVelocity != 0 &&
			rectA.getPosition().y + rectA.getSize().y +3 >= rectB.getPosition().y &&
			rectB.getPosition().y + rectB.getSize().y >= rectA.getPosition().y -3 &&
		rectA.getPosition().x + rectA.getSize().x -3 >= rectB.getPosition().x &&
		rectB.getPosition().x + rectB.getSize().x >= rectA.getPosition().x +3 
		){

		//std::cout << "collision y";
		this->pacman.yVelocity = 0;
	}

	//for (int row = 0; row < 21; row++) {
	//	for (int col = 0; col < 19; col++) {
	//		if (this->pacman.getSprite().getGlobalBounds().intersects(this->tiles[row][col]->getSprite().getGlobalBounds())) {
	//			//set velocity to 0
	//			this->pacman.xVelocity = 0;

	//			this->pacman.yVelocity = 0;
	//		}
	//	}
	//}

}

void GameWorld::update()
{
	this->pollEvents();//do zamkniecia

	if (this->runing()) {//(this->endGame == false
		//int offset_x = 0;
		//int offset_y = 0;
		//if (lewo)
		//	offset_x = -3;
		//if (prawo)
		//	offset_x = 3;
		//if (gora)
		//	offset_y = -3;
		//if (dol)
		//	offset_y = 3;

		//sf::RectangleShape nextPosition;
		//nextPosition.setPosition(this->pacman.pacmanCollision.getPosition().x + offset_x, this->pacman.pacmanCollision.getPosition().y + offset_y);
		//this->updateCollision(nextPosition, this->mapColEl1);

		this->updateCollision(this->pacman.pacmanCollision, this->mapColEl1);
		this->updatePlayer();
	}
}

void GameWorld::updatePlayer()
{
	this->pacman.update();
}

void GameWorld::render()
{
	this->window->clear();

	//render
	this->drawTiles();
	this->pacman.render(this->window);

	this->window->display();
}