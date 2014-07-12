#include "Entity.hpp"
#include <iostream>

////////////////////
//PUBLIC FUNCTIONS//
////////////////////

Entity::Entity() {
	//do nothing
}

Entity::Entity(int tileSize, sf::Vector2i position, sf::Vector2i size, std::vector<std::vector<Entity*>>* entityMap, TileMap* tileMap, sf::Texture* texture) {
	
	//setting variables
	this->tileSize = tileSize;
	this->position = position;
	this->size = size;
	this->entityMap = entityMap;
	this->tileMap = tileMap;
	this->texture = texture;

	//setting original direction
	direction = Direction::UP;

	//making vertices into quad
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(4);

	//positioning vertices
	updateVertices();

	//setting position on texture
	changeTexturePosition(0, 0);

	//placing on entitymap
	placeOnMap();

}

sf::Vector2i Entity::getPosition() {
	return position;
}


/////////////////////
//PRIVATE FUNCTIONS//
/////////////////////

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.texture = texture;
	target.draw(vertices, states);
}

void Entity::updateVertices() {
	
	//changing position into terms of pixels and positioning vertices
	if (direction == Direction::UP) {
		vertices[0].position = (sf::Vector2f)(position * tileSize); //top left
		vertices[1].position = (sf::Vector2f)(position * tileSize + sf::Vector2i(tileSize * size.x, 0)); //top right
		vertices[2].position = (sf::Vector2f)(position * tileSize + sf::Vector2i(tileSize * size.x, tileSize * size.y)); //bottom right
		vertices[3].position = (sf::Vector2f)(position * tileSize + sf::Vector2i(0, tileSize * size.y)); //bottom left
	}
	else if (direction == Direction::DOWN) {
		vertices[2].position = (sf::Vector2f)(position * tileSize);
		vertices[3].position = (sf::Vector2f)(position * tileSize + sf::Vector2i(tileSize * size.x, 0));
		vertices[0].position = (sf::Vector2f)(position * tileSize + sf::Vector2i(tileSize * size.x, tileSize * size.y));
		vertices[1].position = (sf::Vector2f)(position * tileSize + sf::Vector2i(0, tileSize * size.y));
	}
	else if (direction == Direction::LEFT) {
		vertices[1].position = (sf::Vector2f)(position * tileSize); //top left
		vertices[2].position = (sf::Vector2f)(position * tileSize + sf::Vector2i(tileSize * size.x, 0)); //top right
		vertices[3].position = (sf::Vector2f)(position * tileSize + sf::Vector2i(tileSize * size.x, tileSize * size.y)); //bottom right
		vertices[0].position = (sf::Vector2f)(position * tileSize + sf::Vector2i(0, tileSize * size.y)); //bottom left
	}
	else if (direction == Direction::RIGHT) {
		vertices[3].position = (sf::Vector2f)(position * tileSize); //top left
		vertices[0].position = (sf::Vector2f)(position * tileSize + sf::Vector2i(tileSize * size.x, 0)); //top right
		vertices[1].position = (sf::Vector2f)(position * tileSize + sf::Vector2i(tileSize * size.x, tileSize * size.y)); //bottom right
		vertices[2].position = (sf::Vector2f)(position * tileSize + sf::Vector2i(0, tileSize * size.y)); //bottom left
	}
}

void Entity::changeTexturePosition(int x, int y) {

	//changing texture coordinates based off of which frame they are in the texture sheet
	vertices[0].texCoords = sf::Vector2f(x * size.x * tileSize, y * size.y * tileSize);
	vertices[1].texCoords = sf::Vector2f(x * size.x * tileSize + size.x * tileSize, y * size.y * tileSize);
	vertices[2].texCoords = sf::Vector2f(x * size.x * tileSize + size.x * tileSize, y * size.y * tileSize + size.y * tileSize);
	vertices[3].texCoords = sf::Vector2f(x * size.x * tileSize, y * size.y * tileSize + size.y * tileSize);
}

void Entity::placeOnMap() {
	//filling area based on size and position with pointers to self
	for(int a = position.x; a < position.x + size.x; a++) {
		for (int b = position.y; b < position.y + size.y; b++) {
			(*entityMap)[a][b] = this;
		}
	}
}

void Entity::removeFromMap() {
		//filling area based on size and position with NULL pointers
	for(int a = position.x; a < position.x + size.x; a++) {
		for (int b = position.y; b < position.y + size.y; b++) {
			(*entityMap)[a][b] = NULL;
		}
	}
}

bool Entity::mapClear(sf::Vector2i newPosition) {
	//looping through area of given position and size to determine if it is blank on map and within bounds
	for (int a = newPosition.x; a < newPosition.x + size.x; a++) {
		for (int b = newPosition.y; b < newPosition.y + size.y; b++) {
			if (a < 0 || b < 0 || a > (*entityMap).size() - 1 || b > (*entityMap)[0].size() - 1)
				return false;
			if ((*entityMap)[a][b] != NULL)
				return false;
		}
	}

	//returns true if there are no entities in given position
	return true;
}

bool Entity::move(sf::Vector2i deltaPosition) {
	
	//checking if map is clear and position is within bounds
	if (mapClear(position + deltaPosition)) {
		//moving on entity map
		removeFromMap();
		position += deltaPosition;
		placeOnMap();

		//changing direction
		if (deltaPosition.x > 0)
			direction = Direction::RIGHT;
		if (deltaPosition.x < 0)
			direction = Direction::LEFT;
		if (deltaPosition.y > 0)
			direction = Direction::DOWN;
		if (deltaPosition.y < 0)
			direction = Direction::UP;

		//moving vertices for drawing
		updateVertices();
		return true;
	}
	
	return false;
}