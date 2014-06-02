#include "entity.hpp"


Entity::Entity() {
	//todo
}

Entity::Entity(sf::RenderWindow* window, int width, int height, int x, int y, std::map<int, std::map<int, Entity*>>* entitymap) {
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->window = window;
	this->dataType = EntityType::entity;
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

void Entity::updateOnMap() {
	for (int a = x; a < x + width; a++) {
		for (int b = y; b < y + height; b++) {
			(*entitymap)[a][b] = this;
		}
	}
}

void Entity::removeFromMap() {
	for (int a = x; a < x + width; a++) {
		for (int b = y; b < y + height; b++) {
			(*entitymap)[a][b] = NULL;
		}
	}
}

bool Entity::isClear(int x1, int y1, int x2, int y2) {
	for (int a = x1; a < x2; a++) {
		for (int b = y1; b < y2; b++) {
			if ((*entitymap)[a][b] != NULL)
				return false;
		}
	}
	return true;
}

//getters
int Entity::getX() { return x; }
int Entity::getY() { return y; } 
int Entity::getWidth() { return width; }
int Entity::getHeight() { return height; }
int Entity::getDataType(){ return dataType; }


