#include "npc.hpp"
#include <iostream>

NPC::NPC(sf::RenderWindow* window, int width, int height, int x, int y, std::map<int, std::map<int, Entity*>>* entitymap, sf::Clock* timer, std::string type) : Creature(window, width, height, x, y, entitymap, timer){
	texture = Resources::getTexture("npc");
	updateOnMap();
	moveTimer = 0;
	moveTime = 0;

	if (type == "cow") {
		realUpdate = &NPC::cowUpdate;
	}
	initSprite();
}

NPC::~NPC(){
	//todo
}

void NPC::cowUpdate() {
	srand(time(NULL));
	moveTimer += timer->getElapsedTime().asSeconds();
	if (moveTime == 0)
		moveTime = rand() % 5 + 1;
	else if (moveTimer > moveTime) {
		int tempx = x + rand() % 3 - 1;
		int tempy = y + rand() % 3 - 1;
		if (isClear(tempx, tempy, tempx+width, tempy+height)) {
			removeFromMap();
			x = tempx;
			y = tempy;
			updateOnMap();
			moveTime = 0;
			moveTimer = 0;
			sprite.setPosition(x*Tile::tileSize, y*Tile::tileSize);
		}	
	}
}

void NPC::update() {
	(this->*realUpdate)();
}

