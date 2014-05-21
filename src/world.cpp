#include "world.hpp"

World::World(sf::RenderWindow* window, sf::View* view, bool hasSave, sf::Clock* timer) {
	this->window = window;
	this->timer = timer;
	this->x = 0;
	this->y = 0;
	mapSize = 30;

	//loading from file if it exists else generates first 3x3
	std::ifstream isFile("data/world00");
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			if (isFile)
				load(a-1, b-1, a, b);
			else
				generate(a-1, b-1, a, b);
		}
	}
	isFile.close();

	player = new Player(window, 1, 1, 1, 1, view, &entitymap, timer);
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
	std::string type;
	for (int a = mapX*mapSize; a < mapX*mapSize+mapSize; a++) {
		for (int b = mapY*mapSize; b < mapY*mapSize+mapSize; b++) {
			if (rand() % 10 == 0)
				type = "dirt2";
			else
				type = "dirt1";
			tilemaps[arrayX][arrayY][a][b] = new Tile(window, a, b, Tile::tileSize, Tile::tileSize, type);
		}
	}
	save(mapX, mapY, arrayX, arrayY);
}

//////////DRAW//////////
void World::draw()
{
	int dX = window->getSize().x / Tile::tileSize/2 + 1;
	int dY = window->getSize().y / Tile::tileSize/2 + 1;
	
	bool break2;
	//drawing entities & tilemap
	for (int a = player->getX() - dX; a < player->getX() + dX; a++) {
		for (int b = player->getY() - dY; b < player->getY() + dY; b++) {
			for (int c = 0; c < 3; c++) {
				for (int d = 0; d < 3; d++) {
					if (tilemaps[c][d][a][b] != NULL) {
						tilemaps[c][d][a][b]->draw();
						break2 = true;
						break;
					}
				}
				if (break2) {
					break2 = false;
					break;
				}
			}
		}
	}
	player->draw();
}	

//////////UPDATE//////////
void World::update() {
	/*int dX = window->getSize().x / Tile::tileSize/2 + 1;
	int dY = window->getSize().y / Tile::tileSize/2 + 1;
	for (int a = player->getX() - dX; a < player->getX() + dX; a++) {
		for (int b = player->getY() - dY; b < player->getY() + dY; b++) {
			if (entitymap[a][b] != NULL)
				entitymap[a][b]->update();
		}
	}*/
	for (auto npc : npcs) {
		npc->update();
	}
	player->update();

	if (!mapSynced()) {
		updateMaps(currentMap().x, currentMap().y);
	}
}

Player* World::getPlayer()
{
	return player;
}

void World::save(int mapX, int mapY, int arrayX, int arrayY) {
	std::string filename = "data/world"+std::to_string(mapX)+std::to_string(mapY);
	std::ofstream file(filename);
	for (int a = mapX*mapSize; a < mapX*mapSize+mapSize; a++) {
		for (int b = mapY*mapSize; b < mapY*mapSize+mapSize; b++) {
			Tile* tile = tilemaps[arrayX][arrayY][a][b];
			file << tile->getType() << " " << tile->getX() << " " << tile->getY() << std::endl;
		}
	}
	file.close();
}

void World::load(int mapX, int mapY, int arrayX, int arrayY) {
	std::string filename = "data/world" + std::to_string(mapX) + std::to_string(mapY);
	std::ifstream file(filename);
	
	std::string type;
	int tilex;
	int tiley;
	while (!file.eof()) {
		file >> type;
		file >> tilex;
		file >> tiley;
		tilemaps[arrayX][arrayY][tilex][tiley] = new Tile(window, tilex, tiley, Tile::tileSize, Tile::tileSize, type);
	}
	file.close();
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

sf::Vector2<int> World::currentMap() {
	int playerx = player->getX();
	int playery = player->getY();

	if (playerx < 0)
		playerx -= mapSize;
	if (playery < 0)
		playery -= mapSize;
	return sf::Vector2<int>(playerx/mapSize, playery/mapSize);
}

bool World::mapSynced() {
	if (x == currentMap().x && y == currentMap().y)	
		return true;
	return false;
}

bool World::mapExists(int mapX, int mapY) {
	bool exists;
	std::string filename = "data/world" + std::to_string(mapX) + std::to_string(mapY);
	std::ifstream file(filename);
	exists = file;
	file.close();
	return exists;
}

void World::updateMaps(int newx, int newy) {
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			tilemaps[a][b].clear();
			if (mapExists(newx+a-1, newy+b-1))
				load(newx+a-1, newy+b-1, a, b);
			else
				generate(newx+a-1, newy+b-1, a, b);
		}
	}

	x = newx;
	y = newy;
}



