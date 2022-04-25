#include "gameWorld.h"

void GameWorld::initVariables() {
	this->endGame = false;
}

void GameWorld::initWindow() {
	this->videomode = sf::VideoMode(760, 840);
	this->window = new sf::RenderWindow (this->videomode, "Pac-Man", sf::Style::Close | sf::Style::Titlebar);
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

void GameWorld::render()
{
	this->window->clear();

	//render
	this->drawTiles();
	this->pacman.render(this->window);

	this->window->display();
}

void GameWorld::update()
{
	this->pollEvents();//do zamkniecia

	if (this->runing()) {//(this->endGame == false
		this->updatePlayer();
	}
}

void GameWorld::updatePlayer()
{
	this->pacman.update();
}

GameWorld::GameWorld() {
	this->initVariables();
	this->initWindow();

	gridLength = 19;
	gridHeight = 21;
	setUpInitialState();
	setUpTiles();
	drawTiles();
	this->window->setFramerateLimit(60);
}

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
			else if(arr[row][col] == 1) {
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
