#include "world.hpp"

World::World(sf::RenderWindow* window, sf::View* view, bool hasSave, sf::Clock* timer) {
	this->window = window;
	this->timer = timer;
	mapSize = 100;
	

	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			generate(a-1, b-1, a, b);
		}
	}
	player = new Player(window, 1, 1, 1, 1, view, &entitymap, timer);
	wolfie = new NPC(window, 1, 1, 6, 6, &entitymap, timer, "wolf");
}

World::~World(){
	delete player;
}

void World::populate(std::string type, int x1, int y1, int x2, int y2, int chance) {
	srand(time(NULL));

	for (int a = x1; a <= x2; a++) {
		for (int b = y1+1; b <= y2; b++) {
			if (rand() % 100 + 1 <= chance) {
				objects.push_back(new Object(window, 1, 1, a, b, type, &entitymap));
			}
		}
	}
}

void World::paint(std::string type, int x1, int y1, int x2, int y2, int chance) {
	for (int a = x1; a <= x2; a++) {
		for (int b = y1+1; b <= y2; b++) {
			if (rand() % 100 + 1 <= chance) {
				tilemap[a][b] = new Tile(window, a, b, Tile::tileSize, Tile::tileSize, type);
			}
		}
	}
}

void World::generate(int mapX, int mapY, int arrayX, int arrayY) {
	for (int a = mapX*mapSize; a < mapX*mapSize+mapSize; a++) {
		for (int b = mapY*mapSize; b < mapY*mapSize+mapSize; b++) {
			tilemaps[arrayX][arrayY][a][b] = new Tile(window, a, b, Tile::tileSize, Tile::tileSize, "grass");
		}
	}
}

void World::draw()
{
	int dX = window->getSize().x / Tile::tileSize/2 + 1;
	int dY = window->getSize().y / Tile::tileSize/2 + 1;

	//drawing entities & tilemap
	for (int a = player->getX() - dX; a < player->getX() + dX; a++) {
		for (int b = player->getY() - dY; b < player->getY() + dY; b++) {
			for (int c = 0; c < 3; c++) {
				for (int d = 0; d < 3; d++) {
					if (tilemaps[c][d][a][b] != NULL) 
						tilemaps[c][d][a][b]->draw();
					}
				}
			if (entitymap[a][b] != NULL)
				entitymap[a][b]->draw();
		}
	}
	//entitymap[1][1]->draw();
}	

void World::update() {
	int dX = window->getSize().x / Tile::tileSize/2 + 1;
	int dY = window->getSize().y / Tile::tileSize/2 + 1;
	for (int a = player->getX() - dX; a < player->getX() + dX; a++) {
		for (int b = player->getY() - dY; b < player->getY() + dY; b++) {
			if (entitymap[a][b] != NULL)
				entitymap[a][b]->update();
		}
	}
}

Player* World::getPlayer()
{
	return player;
}

void World::save() {
}

void World::load() {
}

bool World::isClear(int x1, int y1, int x2, int y2) {
	for (int a = x1; a < x2; a++) {
		for (int b = y1; b < y2; b++) {
			if (entitymap[a][b] != NULL)
				return false;
		}
	}
	return true;
}

