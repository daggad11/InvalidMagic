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
	 void draw();
	 void update(double time);
	 void save();
	 void load();
	 Player* getPlayer();
	~ World();

	//generation functions
	void generate(int width, int height);
	void populate(std::string type, int x1, int y1, int x2, int y2, int chance);
private:
	Player *player;
	std::map<int, std::map<int, Tile*>> tilemap;
	std::map<int, std::map<int, Entity*>> entitymap; 
	std::vector<Object*> objects;
	sf::RenderWindow* window;
};
#endif
