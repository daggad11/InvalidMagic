#include "world.hpp"

World::World(sf::RenderWindow* window, sf::View* view, bool hasSave) {
	this->window = window;
	
	if (hasSave)
		load();
	else 
		generate(100, 100);
	
	player = new Player(window, 1, 1, 1, 1, view, &entitymap);
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

void World::generate(int width, int height) {
	for (int a = 0; a < width; a++) {
		for (int b = 0; b < height; b++) {
			tilemap[a][b] = new Tile(window, a, b, Tile::tileSize, Tile::tileSize, "dirt1");
		}
	}
	populate("rock", 0, 0, width - 1, height - 1, 1);
	paint("dirt2", 0, 0, 99, 99, 1);
}

void World::draw()
{
	int dX = window->getSize().x / Tile::tileSize/2 + 1;
	int dY = window->getSize().y / Tile::tileSize/2 + 1;

	//drawing entities & tilemap
	for (int a = player->getX() - dX; a < player->getX() + dX; a++) {
		for (int b = player->getY() - dY; b < player->getY() + dY; b++) {
			if (tilemap[a][b] != NULL)
				tilemap[a][b]->draw();
			if (entitymap[a][b] != NULL)
				entitymap[a][b]->draw();
		}
	}
}	

void World::update(double time) {
	player->update(time);
}

Player* World::getPlayer()
{
	return player;
}

void World::save() {
}

void World::load() {
}

