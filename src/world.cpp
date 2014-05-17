#include "world.hpp"

World::World(sf::RenderWindow* window) {
	this->window = window;

	//tilemap
	textures.push_back(sf::Texture());
	textures[0].loadFromFile("resources/dirt1.png");
	for (int a = 0; a < 800/32; a++) {
		tiles.push_back(std::vector<Tile>());
		for (int b = 0; b < 640/32; b++) {
			tiles[a].push_back(Tile(window, a, b, 32, 32, &(textures[0])));
		}
	}
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
