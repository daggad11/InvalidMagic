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
	this->texture = texture;
	
	sprite.setTexture(*texture);
	sprite.setScale((float)Tile::tileSize/texture->getSize().x*width, (float)Tile::tileSize/texture->getSize().y*height);
	sprite.setPosition(x*Tile::tileSize, y*Tile::tileSize);
}

Entity::~Entity() {
	//todo
}

void Entity::draw() {
	window->draw(sprite);
}

//getters
int Entity::getX() { return x; }
int Entity::getY() { return y; } 



