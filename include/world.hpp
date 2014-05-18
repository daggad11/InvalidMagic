//this is the world header file
#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include "tile.hpp"
#include "player.hpp"
#include "object.hpp"

class World
{
public:
	 World();
	 World(sf::RenderWindow* window, sf::View* view, bool hasSave);
	 void generate();
	 void draw();
	 void update(double time);
	 void save();
	 void load();
	 Player* getPlayer();
	~ World();
private:
	Player player;
	std::vector<std::vector<Tile>> tiles;
	std::vector<sf::Texture*> textures;
	std::map<int, std::map<int, Entity*>> tilemap; 
	std::vector<Object> objects;
	sf::RenderWindow* window;
};
#endif
