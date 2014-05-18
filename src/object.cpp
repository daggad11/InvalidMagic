#include "object.hpp"


Object::Object(sf::RenderWindow* window, int width, int height, int x, int y, sf::Texture* texture, std::string type) : Entity(window, width, height, x, y, texture, mass){
	int mass;
	if(type=="tree"){
		solid = true;
		durability = 50;
		mass = 200;
	}
	else if(type=="rock"){
		solid = true;
		durability = 9001;
		mass = 500;
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
