#include "World.hpp"
#include <iostream>

////////////////////
//PUBLIC FUNCTIONS//
////////////////////

World::World(sf::Clock* timer) {
	this->timer = timer;

	//creating textures
	textures[Texture::PLAYER] = sf::Texture();

	//loading textures
	textures[Texture::PLAYER].loadFromFile("resources/player.png");

	//creating 10x10 tileMap
	genMap(100, 100);

	//creating player
	player = Player(timer, 64, sf::Vector2i(1, 1), sf::Vector2i(1, 1), &entityMap, &tileMap, &textures[Texture::PLAYER]);
}


void World::update() {
	player.update();
}

Player* World::getPlayer() {
	return &player;
}

/////////////////////
//PRIVATE FUNCTIONS//
/////////////////////

void World::genMap(int width, int height) {
	
	//seeding random num generator
	srand (time(NULL));

	//pushing back dirt into a vector to pass to tilemap and pushing back nulls into entitymap
	std::vector<std::vector<int>> tempTiles;
	for (int a = 0; a < width; a++) {
		entityMap.push_back(std::vector<Entity*>());
		tempTiles.push_back(std::vector<int>());
		
		for (int b = 0; b < height; b++) {
			//generating random dirt
			tempTiles[a].push_back(rand() % 3);
			entityMap[a].push_back(NULL);
		}
	}

	//generating tilemap
	tileMap.load(tempTiles, "resources/tiles.jpg", 64);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(tileMap, states);
	target.draw(player);
}