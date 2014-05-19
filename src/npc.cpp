#include "npc.hpp"

NPC::NPC(sf::RenderWindow* window, int width, int height, int x, int y, std::map<int, std::map<int, Entity*>>* entitymap, sf::Clock* timer) : Creature(window, width, height, x, y, entitymap, timer){
	texture = Resources::getTexture("npc");
	initSprite();
	(*entitymap)[x][y] = this;
}

NPC::~NPC(){
	//todo
}

void NPC::update() {

}

