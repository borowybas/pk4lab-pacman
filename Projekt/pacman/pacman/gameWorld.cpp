#include "gameWorld.h"
#include <iostream>
#include <thread>
#include <regex>

GameWorld::GameWorld() {
	this->initWindow();

	this->path = "C:\\Users\\Admin\\Documents\\GitHub\\a87312ac-gr41-repo\\Projekt\\pacman\\images";
	setUpTiles();
	drawTiles();
	this->window->setFramerateLimit(60);

	setUpCollisionVector();
	font.loadFromFile("C:\\Users\\Admin\\Documents\\GitHub\\a87312ac-gr41-repo\\Projekt\\pacman\\joystix monospace.ttf");
	this->text.setFont(this->font);

	std::string str = std::to_string(this->score);
	text.setString(str);

	this->ghostVec.push_back(new RedGhost);
	this->ghostVec.push_back(new BlueGhost);
	this->ghostVec.push_back(new OrangeGhost);
	this->ghostVec.push_back(new PinkGhost);
}

GameWorld::~GameWorld() {
	for (std::vector<GameTile*> vec : this->tiles) {
		for (GameTile* element : vec) {
			delete element;
		}
	}
	for (Ghost* ghost : this->ghostVec) {
		delete ghost;
	}
	this->tiles.clear();
	delete this->window;
}

void GameWorld::initWindow() {
	this->videomode = sf::VideoMode(760, 840);
	this->window = new sf::RenderWindow(this->videomode, "Pac-Man", sf::Style::Close | sf::Style::Titlebar);
}

void GameWorld::setUpTiles() {
	tiles.clear();
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
		{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	};
	std::string bluePath;	std::string pointPath;	std::string blackPath;

	std::regex blueReg("blueT[a-zA-Z]+", std::regex_constants::icase);
	std::regex blackReg("bla[a-zA-Z]+", std::regex_constants::icase);
	std::regex pointReg("p[a-zA-Z]+", std::regex_constants::icase);
	
	for (auto& p1 : std::filesystem::directory_iterator(this->path)) {
		if (std::regex_match(p1.path().stem().string(), blueReg)) {
			bluePath = p1.path().string();
		}
		else if (std::regex_match(p1.path().stem().string(), blackReg)) {
			blackPath = p1.path().string();
		}
		else if (std::regex_match(p1.path().stem().string(), pointReg)) {
			pointPath = p1.path().string();
		}
	}

	for (int row = 0; row < 21; row++) {
		std::vector<GameTile* > wholeRow;
		int y = row * 40;
		for (int col = 0; col < 19; col++) {
			int x = col * 40;
			if (arr[row][col] == 0) {
				wholeRow.push_back(new GameTile(bluePath, x, y));
			}
			else if (arr[row][col] == 1) {
				wholeRow.push_back(new Point(pointPath, x, y));
			}
		}
		tiles.push_back(wholeRow);
	}
}

void GameWorld::drawTiles()
{
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 19; j++) {
			if(this->tiles[i][j]->eaten == false)
				this->window->draw(this->tiles[i][j]->tile_sprite);
		}
	}
}

void GameWorld::setMapColPos()
{
	sf::RectangleShape tempShape;
	sf::Vector2f size;

	tempShape.setPosition(20, 20); //1
	size.x = 760; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//2
	tempShape.setPosition(380, 60); //360+20
	size.x = 40; size.y = 80;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//3
	tempShape.setPosition(20, 60); 
	size.x = 40; size.y = 200;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//4
	tempShape.setPosition(100, 100);
	size.x = 80; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//5
	tempShape.setPosition(220, 100);
	size.x = 120; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//6
	tempShape.setPosition(460, 100);
	size.x = 120; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//7
	tempShape.setPosition(620, 100);
	size.x = 80; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//8
	tempShape.setPosition(740, 60);
	size.x = 40; size.y = 200;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//9
	tempShape.setPosition(100, 180);
	size.x = 80; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//10
	tempShape.setPosition(220, 180);
	size.x = 40; size.y = 200;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//11
	tempShape.setPosition(300, 180);
	size.x = 200; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//12
	tempShape.setPosition(540, 180);
	size.x = 40; size.y = 200;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//13
	tempShape.setPosition(620, 180);
	size.x = 80; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//14
	tempShape.setPosition(380, 220);
	size.x = 40; size.y = 80;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//15
	tempShape.setPosition(20, 260);
	size.x = 120; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//16
	tempShape.setPosition(140, 260);
	size.x = 40; size.y = 120;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//17
	tempShape.setPosition(260, 260);
	size.x = 80; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//18
	tempShape.setPosition(460, 260);
	size.x = 80; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//19
	tempShape.setPosition(620, 260);
	size.x = 40; size.y = 120;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//20
	tempShape.setPosition(660, 260);
	size.x = 120; size.y = 40 ;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//21
	tempShape.setPosition(20, 340);
	size.x = 120; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//22
	tempShape.setPosition(300, 340);
	size.x = 40; size.y = 120;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//23
	tempShape.setPosition(340, 340);
	size.x = 120; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//24
	tempShape.setPosition(460, 340);
	size.x = 40; size.y = 120;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//25
	tempShape.setPosition(660, 340);
	size.x = 120; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	//26
	tempShape.setPosition(20, 420);
	size.x = 120; size.y = 40;
	tempShape.setSize(size);
	colElements1.push_back(tempShape);
	
}
void GameWorld::setMapColPos2()
{
	sf::RectangleShape tempShape;
	sf::Vector2f size;
	//27
	tempShape.setPosition(140, 420);
	size.x = 40; size.y = 120;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//28
	tempShape.setPosition(220, 420);
	size.x = 40; size.y = 120;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//29
	tempShape.setPosition(340, 420);
	size.x = 120; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//30
	tempShape.setPosition(540, 420);
	size.x = 40; size.y = 120;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//31
	tempShape.setPosition(620, 420);
	size.x = 40; size.y = 120;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//32
	tempShape.setPosition(660, 420);
	size.x = 120; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//33
	tempShape.setPosition(20, 500);
	size.x = 120; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//34
	tempShape.setPosition(300, 500);
	size.x = 200; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//35
	tempShape.setPosition(660, 500);
	size.x = 120; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//36
	tempShape.setPosition(20, 540);
	size.x = 40; size.y = 320;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//37
	tempShape.setPosition(380, 540);
	size.x = 40; size.y = 80;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//38
	tempShape.setPosition(740, 540);
	size.x = 40; size.y = 320;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//39
	tempShape.setPosition(100, 580);
	size.x = 80; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//40
	tempShape.setPosition(220, 580);
	size.x = 120; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//41
	tempShape.setPosition(460, 580);
	size.x = 120; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//42
	tempShape.setPosition(620, 580);
	size.x = 80; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//43
	tempShape.setPosition(140, 620);
	size.x = 40; size.y = 80;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//44
	tempShape.setPosition(620, 620);
	size.x = 40; size.y = 80;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//45
	tempShape.setPosition(60, 660);
	size.x = 40; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//46
	tempShape.setPosition(220, 680);
	size.x = 40; size.y = 80;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//47
	tempShape.setPosition(300, 660);
	size.x = 200; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//48
	tempShape.setPosition(540, 680);
	size.x = 40; size.y = 80;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//49
	tempShape.setPosition(700, 660);
	size.x = 40; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//50
	tempShape.setPosition(380, 700);
	size.x = 40; size.y = 80;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//51
	tempShape.setPosition(100, 740);
	size.x = 240; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//52
	tempShape.setPosition(460, 740);
	size.x = 240; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
	//53
	tempShape.setPosition(20, 820);
	size.x = 760; size.y = 40;
	tempShape.setSize(size);
	colElements2.push_back(tempShape);
}

void GameWorld::setUpCollisionVector()
{
	std::thread th1(&GameWorld::setMapColPos, this);
	std::thread th2(&GameWorld::setMapColPos2, this);

	th1.join(); th2.join();
	colElements1.insert(colElements1.end(), colElements2.begin(), colElements2.end());
}

void GameWorld::pollEvents()
{
	while (this->window->pollEvent(this->myEvent)) {
		if (this->myEvent.type == sf::Event::Closed) {//
			this->window->close();
		}
	}
}

void GameWorld::render()
{
	this->window->clear();
	this->drawTiles();
	this->pacman.render(this->window);
	for (int i = 0; i < ghostVec.size(); i++) {
		this->ghostVec[i]->render(this->window);
	}
	this->window->draw(text);
	this->window->draw(endText);
	this->window->display();
}

void GameWorld::update()
{
	this->pollEvents();

	if (this->runing()) {
		if (this->pacman.isAlive == 1 && this->score < 1850) {
			for (int i = 0; i <= colElements1.size(); i++) {
				this->updateCollision(this->pacman.pacmanCollision, this->colElements1[i]);
			}
			this->updatePlayers();
			this->updateEating(this->pacman.pacmanCollision);
			this->updateDisplayScore();
			for (int i = 0; i < ghostVec.size(); i++) {
				this->updatePacGhostCollision(this->pacman.pacmanCollision, this->ghostVec[i]->ghostCollision);
			}
		}
		else {
			this->displayEndState(this->pacman.isAlive);
		}
	}
}

void GameWorld::updatePlayers()
{
	this->pacman.update();
	for (int i = 0; i < ghostVec.size(); i++) {
		this->ghostVec[i]->updateGhost();
	}
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
	}
	else if (this->pacman.yVelocity != 0 &&
			rectA.getPosition().y + rectA.getSize().y +3 >= rectB.getPosition().y &&
			rectB.getPosition().y + rectB.getSize().y >= rectA.getPosition().y -3 &&
			rectA.getPosition().x + rectA.getSize().x -3 >= rectB.getPosition().x &&
			rectB.getPosition().x + rectB.getSize().x >= rectA.getPosition().x +3 
			){
		this->pacman.yVelocity = 0;
	}
}

void GameWorld::updateEating(const sf::RectangleShape& rectA)
{
	sf::RectangleShape tempShape;
	sf::Vector2f size(40, 40);
	tempShape.setSize(size);
	for (int row = 1; row < 20; row++) {
		for (int col = 0; col < 19; col++) {
			if (this->tiles[row][col]->isFood && this->tiles[row][col]->eaten == false) {//jeœli jest niezjedzonym jedzeniem
				tempShape.setPosition(col*40 + 20, row*40 + 20);
				foodRectangles.push_back(tempShape);
				//sprawdŸ kolizjê
				if (rectA.getPosition().x + rectA.getSize().x - 20>= tempShape.getPosition().x && //->
					tempShape.getPosition().x + tempShape.getSize().x >= rectA.getPosition().x + 20&& //<-
					rectA.getPosition().y + rectA.getSize().y - 20>= tempShape.getPosition().y &&
					tempShape.getPosition().y + tempShape.getSize().y >= rectA.getPosition().y + 20
					) {
					this->tiles[row][col]->eaten = true;
					this->score += 10;
				}
			}
		}
	}
}

void GameWorld::updateDisplayScore()
{
	std::string str = std::to_string(this->score);
	text.setString(str);
}

void GameWorld::updatePacGhostCollision(const sf::RectangleShape& tempPacShape, const sf::RectangleShape& tempGhostShape){
	if (tempPacShape.getPosition().x + tempPacShape.getSize().x >= tempGhostShape.getPosition().x && //->
		tempGhostShape.getPosition().x + tempGhostShape.getSize().x >= tempPacShape.getPosition().x && //<-
		tempPacShape.getPosition().y + tempPacShape.getSize().y >= tempGhostShape.getPosition().y &&
		tempGhostShape.getPosition().y + tempGhostShape.getSize().y >= tempPacShape.getPosition().y
		) {
		this->pacman.isAlive = 0;
	}
}

void GameWorld::displayEndState(bool pacState)//nie zyje
{
	this->endText.setFont(this->font);
	this->endText.setCharacterSize(50);
	this->endText.setPosition(sf::Vector2f(220, 300));
	if (pacState == 0) {
		endText.setString("YOU DIED");
	}
	else {
		endText.setString("YOU WON");
	}
}