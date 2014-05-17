//this is the world header file
#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "tile.hpp"
#include "player.hpp"

class World
{
public:
	 World();
	 World(sf::RenderWindow* window);
	 void draw();
	~ World();
private:
	std::vector<std::vector<Tile>> tiles;
	std::vector<sf::Texture> textures;
	sf::RenderWindow* window;
};
#endif
