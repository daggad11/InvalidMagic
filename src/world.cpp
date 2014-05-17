#include "world.hpp"

World::World()
{
	//default constructor. 
}

World::World(sf::RenderWindow* window){
	this->window = window;
	textures.push_back(sf::texture());
	textures[0].loadFromFile("../resources/dirt1.png")
	tiles.push_back(Tile(window, 1, 1, 16, 16, &(textures[0])));
}

World::~World(){
	//tonodo
}

void World::draw()
{
	for (auto tile: tiles)
		tile.draw();
}

Player* World::getPlayer()
{
	return &p;
}