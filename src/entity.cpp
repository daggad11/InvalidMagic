#include "entity.hpp"
#include <iostream>


Entity::Entity() {
	//todo
}

Entity::Entity(sf::RenderWindow* window, int width, int height, int x, int y, int mass, std::map<int, std::map<int, Entity*>>* entitymap) {
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->mass = mass;
	this->window = window;
	this->entitymap = entitymap;
}

Entity::~Entity() {
	//todo
}

void Entity::draw() {
	window->draw(sprite);
}

void Entity::initSprite() {
	sprite.setScale((float)Tile::tileSize/texture->getSize().x*width, (float)Tile::tileSize/texture->getSize().y*height);
	sprite.setPosition(x*Tile::tileSize, y*Tile::tileSize);
	sprite.setTexture(*texture);
}

//getters
int Entity::getX() { return x; }
int Entity::getY() { return y; } 
int Entity::getWidth() { return width; }
int Entity::getHeight() { return height; }
int Entity::getMass() { return mass; } 


