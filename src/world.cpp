#include "world.hpp"

World::World(sf::RenderWindow* window) {
	this->window = window;
	textures.push_back(sf::Texture());
	textures[0].loadFromFile("../resources/dirt1.png");
	tiles[0].push_back(Tile(window, 1, 1, 16, 16, &(textures[0])));
}

World::~World(){
	//tonodo
}

void World::draw()
{
	for (auto row: tiles)
		for (auto tile : row)
			tile.draw();
}

Player* World::getPlayer()
{
	return &p;
}
