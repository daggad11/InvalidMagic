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

bool Object::getMovable(){
	return movable;
}

void Object::setMovable(bool m){
	this->movable = m;
}

Object::~Object(){
	//todo
}
