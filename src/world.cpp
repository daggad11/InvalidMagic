#include "world.hpp"

World::World(sf::RenderWindow* window, sf::View* view, bool hasSave) {
	this->window = window;

	textures.push_back(new sf::Texture());
	textures.push_back(new sf::Texture());
	textures.push_back(new sf::Texture());
	textures[0]->loadFromFile("resources/dirt1.png");
	textures[1]->loadFromFile("resources/grass.png");
	textures[2]->loadFromFile("resources/player.png");
	
	if (hasSave)
		load();
	else
		generate();

	player = Player(window, 1, 1, 1, 1, textures[2], 1, view);
}

World::~World(){
	//tonodo
}

void World::generate() {
	srand(time(NULL));



	//drawing grass
	for (int a = 0; a < 100; a++) {
		tiles.push_back(std::vector<Tile>());
		for (int b = 0; b < 100; b++) {
			tiles[a].push_back(Tile(window, a, b, Tile::tileSize, Tile::tileSize, textures[1], 1));
		}
	}
	
	int ypos = rand() % 10;
	for (int a = 0; a < 99; a++) {
		for (int b = 0; b < rand() % 3 + 4; b++) {
			tiles[a][ypos] = Tile(window, a, ypos, Tile::tileSize, Tile::tileSize, textures[0], 0);
			tiles[a+1][ypos] = Tile(window, a+1, ypos, Tile::tileSize, Tile::tileSize, textures[0], 0);
			if (rand() % 2 && ypos < 99)
				ypos++;
			else if (ypos > 0)
				ypos--;
		}
	}


}

void World::draw()
{
	for (auto row: tiles)
		for (auto tile : row)
			tile.draw();

	player.draw();
}

void World::update(double time) {
	player.update(time);
}

Player* World::getPlayer()
{
	return &player;
}

void World::save() {
	std::ofstream file("data/world.save");
	file << tiles.size() << " " << tiles[0].size() << std::endl;
	for (auto row : tiles) {
		for (auto tile : row) {
			file << tile.getType() << " ";
		}
		file << std::endl;
	}
	file.close();
}

void World::load() {
	std::ifstream file("data/world.save");
	int tilesX, tilesY;
	file >> tilesX;
	file >> tilesY;
	std::cout << tilesX << " " << tilesY << std::endl;
	for (int a = 0; a < tilesX; a++) {
		tiles.push_back(std::vector<Tile>());
		for (int b = 0; b < tilesY; b++) {
			int value;
			file >> value;
			tiles[a].push_back(Tile(window, a, b, Tile::tileSize, Tile::tileSize, textures[value], value));
		}
	}
	file.close();
}
