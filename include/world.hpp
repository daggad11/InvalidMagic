//this is the world header file
#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "tile.hpp"

class World
{
public:
	 World();
	 World(sf::RenderWindow* window);
	~ World();
private:
	std::vector<std::vector<Tile>> tiles;
	sf::RenderWindow* window;
};
#endif
