#include "npc.hpp"
#include <iostream>

NPC::NPC(sf::RenderWindow* window, int width, int height, int x, int y, std::map<int, std::map<int, Entity*>>* entitymap, sf::Clock* timer, std::string type) : Creature(window, width, height, x, y, entitymap, timer){
	texture = Resources::getTexture("npc");
	updateOnMap();
	moveTimer = 0;
	moveTime = 0;
	isAggro = false;
	dataType = EntityType::npc;
	if (type == "cow") {
		realUpdate = &NPC::passiveUpdate;//change this to cowUpdate when notes in said method are implememted.
	}
	else if (type == "wolf"){
		realUpdate = &NPC::wolfUpdate;

	}
	initSprite();
}

NPC::~NPC(){
	//todo
}

void NPC::passiveUpdate(){
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
void NPC::cowUpdate() {
	//need to implement something that runs when attacked, after attacking is actually a thing...

}


void NPC::wolfUpdate(){
	srand(time(NULL));
	moveTimer += timer->getElapsedTime().asSeconds();
	if(moveTimer > 3.0) {
		int tmpX = 0;
		int tmpY = 0;
		for (int i = 0; i < 5; i++){
			for (int j = 0; j < 5; j++){
				if((*entitymap)[i][j] != NULL){
					if((*entitymap)[i][j]->getDataType() == EntityType::player){
						isAggro = true;
						tmpX = i;
						tmpY = j;
					}//records the coords of a player to move towards. 
				}
			}
		}
		if(isAggro == true){
			removeFromMap();
			if(tmpX>x) { x++; }
			else{ x--; }
			if(tmpY>y){	y++; }
			else{ y--; }
			updateOnMap();
			sprite.setPosition(x*Tile::tileSize, y*Tile::tileSize);
		}//this increments towards a player!

		isAggro = false;
		moveTimer = 0;
	}

}

void NPC::update() {
	(this->*realUpdate)();
}

