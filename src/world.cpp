#include "world.hpp"

World::World(sf::RenderWindow* window, sf::View* view, bool hasSave) {
	this->window = window;
	
	if (hasSave)
		load();
	else
		generate();
	
	player = new Player(window, 1, 1, 1, 1, 1, view, &tilemap);
}

World::~World(){
	delete player;
}

void World::generate() {
	srand(time(NULL));

	//drawing grass
	for (int a = 0; a < 100; a++) {
		tiles.push_back(std::vector<Tile>());
		for (int b = 0; b < 100; b++) {
			tiles[a].push_back(Tile(window, a, b, Tile::tileSize, Tile::tileSize, "grass"));
		}
	}
	
	int ypos = rand() % 10;
	std::string type;
	for (int a = 0; a < 99; a++) {
		for (int b = 0; b < rand() % 3 + 4; b++) {
			
			if (rand() % 10 == 8)//specifically 8
				type = "dirt1";
			else
				type = "dirt2";

			tiles[a][ypos] = Tile(window, a, ypos, Tile::tileSize, Tile::tileSize, type);
			
			if (rand() % 10 == 8)//specifically 8
				type = "dirt1";
			else
				type = "dirt2";

			tiles[a+1][ypos] = Tile(window, a+1, ypos, Tile::tileSize, Tile::tileSize, type);
			if (rand() % 2 && ypos < 99)
				ypos++;
			else if (ypos > 0)
				ypos--;
		} 
	}

	objects.push_back(new Object(window, 1, 1, 4, 4, "rock", &tilemap));
	
}

void World::draw()
{
	int dX = window->getSize().x / Tile::tileSize/2 + 1;
	int dY = window->getSize().y / Tile::tileSize/2 + 1;

	//drawing tiles
	for (int a = player->getX() - dX; a < player->getX() + dX; a++) {
		for (int b = player->getY() - dY; b < player->getY() + dY; b++) {
			if (a >= 0 && b > 0 && a < tiles.size() && b < tiles[0].size())
				if (a >= 0 && b >= 0 && a < tiles.size() && b < tiles[0].size()) 
					tiles[a][b].draw();
		}
	}
	
	//drawing entities
	for (int a = player->getX() - dX; a < player->getX() + dX; a++) {
		for (int b = player->getY() - dY; b < player->getY() + dY; b++) {
			if (tilemap[a][b] != NULL)
				tilemap[a][b]->draw();
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
	std::ofstream file("data/world.save");
	file << tiles.size() << " " << tiles[0].size() << std::endl;

	//save tiles
	for (auto row : tiles) {
		for (auto tile : row) {
			file << tile.getType() << " " ;
		}
		file << std::endl;
	}

	//save objects
	file << objects.size() << std::endl;
	for (auto object : objects) {
		file << object->getWidth() << " " << object->getHeight() << " " << object->getX() << " " << object->getY() << " " << object->getType() << std::endl;
	}
	file.close();
}

void World::load() {
	std::ifstream file("data/world.save");
	int tilesX, tilesY;
	file >> tilesX;
	file >> tilesY;

	//loading tiles
	std::string value;
	for (int a = 0; a < tilesX; a++) {
		tiles.push_back(std::vector<Tile>());
		for (int b = 0; b < tilesY; b++) {
			file >> value;
			tiles[a].push_back(Tile(window, a, b, Tile::tileSize, Tile::tileSize, value));
		}
	}
	//loading objects
	int numberOfObjects;
	file >> numberOfObjects;
	for (int a = 0; a < numberOfObjects; a++) {
		int width, height, x, y;
		std::string type;
		file >> width;
		file >> height;
		file >> x;
		file >> y;
		file >> type;
		objects.push_back(new Object(window, width, height, x, y, type, &tilemap));
	}

	file.close();
	std::cout << "World Loaded" << std::endl;
}
