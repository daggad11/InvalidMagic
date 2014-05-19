#include "npc.hpp"
#include <iostream>

NPC::NPC(sf::RenderWindow* window, int width, int height, int x, int y, std::map<int, std::map<int, Entity*>>* entitymap, sf::Clock* timer) : Creature(window, width, height, x, y, entitymap, timer){
	texture = Resources::getTexture("npc");
	initSprite();
	(*entitymap)[x][y] = this;
	moveTimer = 0;
	moveTime = 0;
}

NPC::~NPC(){
	//todo
}

void NPC::update() {
	srand(time(NULL));
	moveTimer += timer->getElapsedTime().asSeconds();
	if (moveTime == 0)
		moveTime = rand() % 5 + 1;
	else if (moveTimer > moveTime) {
		int tempx = x + rand() % 3 - 1;
		int tempy = y + rand() % 3 - 1;
		if ((*entitymap)[tempx][tempy] == NULL) {
			(*entitymap)[x][y] = NULL;
			x = tempx;
			y = tempy;
			(*entitymap)[tempx][tempy] = this;
			moveTime = 0;
			moveTimer = 0;
			sprite.setPosition(x*Tile::tileSize, y*Tile::tileSize);
		}	
	}

}

