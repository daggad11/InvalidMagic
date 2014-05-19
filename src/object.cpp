#include "object.hpp"

Object::Object(sf::RenderWindow* window, int width, int height, int x, int y, std::string type, std::map<int, std::map<int, Entity*>>* entitymap) : Entity(window, width, height, x, y, mass, entitymap) {
	this->type = type;

	if(type=="tree"){
		solid = true;
		durability = 50;
		mass = 200;
	}
	else if(type=="rock"){
		solid = true;
		durability = 9001;
		mass = 500;
		texture = Resources::getTexture("rock");
	}
	initSprite();

	for (int a = x; a < x + width; a++) {
		for (int b = y; b < y + width; b++) {
			(*entitymap)[a][b] = this;
		} 
	}

}


bool Object::getSolid(){
	return solid;
}

void Object::setSolid(bool s){
	this->solid = s;
}

int Object::getDurability(){
	return durability;
}

void Object::setDurability(int newDur){
	this->durability = newDur;
}

std::string Object::getType(){
	return type;
}

void Object::setType(std::string t){
	this->type = t; 
}

void Object::breakThisObject(int reducedBy){
	durability -= reducedBy;
	if(durability<0){
		delete this;
	}
}
Object::~Object(){
	//todo
}
