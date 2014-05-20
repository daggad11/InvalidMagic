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
#include "npc.hpp"

class World
{
public:
	 World();
	 World(sf::RenderWindow* window, sf::View* view, bool hasSave, sf::Clock* timer);
	 void draw();
	 void update();
	 void save();
	 void load();
	 Player* getPlayer();
	~ World();

	//generation functions
	void generate(int width, int height, int arrayX, int arrayY);
	void populate(std::string type, int x1, int y1, int x2, int y2, int chance);
	void paint(std::string type, int x1, int y1, int x2, int y2, int chance);
private:
	int mapSize;
	sf::Clock* timer;
	Player *player;
	std::map<int, std::map<int, Tile*>> tilemap;
	std::map<int, std::map<int, Entity*>> entitymap; 
	std::vector<Object*> objects;
	std::vector<NPC*> npcs;
	std::map<int, std::map<int, Tile*>> tilemaps[3][3];
	sf::RenderWindow* window;
	bool isClear(int x1, int y1, int x2, int y2);
};
#endif
