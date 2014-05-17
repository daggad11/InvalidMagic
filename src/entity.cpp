#include "entity.hpp"

Entity::Entity() {
	//todo
}

Entity::Entity(sf::RenderWindow* window, int width, int height, int x, int y, sf::Texture* texture, int mass) {
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->mass = mass;
	this->window = window;
}

Entity::~Entity() {
	//todo
}


